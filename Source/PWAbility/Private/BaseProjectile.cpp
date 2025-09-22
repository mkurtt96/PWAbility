// copyright Iompa


#include "BaseProjectile.h"

#include "AbilityEnums.h"
#include "MyEffectActor.h"
#include "Ability/SpellParams.h"
#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "Components/WProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "PWAbility.h"
#include "Ability/Damageable.h"
#include "Ability/Effectable.h"
#include "Ability/PWEffectReceiverInterface.h"

ABaseProjectile::ABaseProjectile()
{
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetCollisionObjectType(ECC_Projectile);
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Sphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	Sphere->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	Sphere->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	Sphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap);
	//Sphere->SetCollisionResponseToChannel(ECC_PawnOverlap, ECR_Overlap);
	SetRootComponent(Sphere);

	ProjectileMovement = CreateDefaultSubobject<UWProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovement->SetIsReplicated(true);
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->ProjectileGravityScale = 0;
}

void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
		SetLifeSpan(CalculateLifeTime());

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ABaseProjectile::OnOverlap);
	LoopingSound = UGameplayStatics::SpawnSoundAttached(ActiveSoundLoop, GetRootComponent());
}

void ABaseProjectile::Destroyed()
{
	Super::Destroyed();

	Sphere->OnComponentBeginOverlap.RemoveDynamic(this, &ABaseProjectile::OnOverlap);

	if (LoopingSound)
	{
		LoopingSound->Stop();
		LoopingSound->DestroyComponent();
	}
}

bool ABaseProjectile::ShouldIgnoreOverlap(const AActor* OtherActor) const
{
	if (IsNoCollision(this))
		return true;

	if (IsDontTriggerCollision(OtherActor))
		return true;

	return false;
}

bool ABaseProjectile::CanHitTarget(const AActor* OtherActor)
{
	if (!bCanHitTheSameTarget)
	{
		if (LastHitActor == OtherActor)
			return false;
	}

	const float* LastTime = LastHitTimes.Find(OtherActor);
	float Now = GetWorld()->GetTimeSeconds();
	return (!LastTime || Now - *LastTime >= TargetHitCooldown);
}

void ABaseProjectile::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor || OtherActor == this) return;
	if (ShouldIgnoreOverlap(OtherActor)) return;
	if (IsActorProjectile(OtherActor))
	{
		HandleProjectileCollision(OtherActor);
		return;
	}
	if (!CanHitTarget(OtherActor)) return;
	if (!SpellParams) return;
	if (!CheckForCollisionTarget(OtherActor)) return;

	LastHitActor = OtherActor;
	LastHitTimes.FindOrAdd(OtherActor) = GetWorld()->GetTimeSeconds();
	HitCount++;

	if (HitCount == DestroyOnHit)
		Sphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	OnProjectileOverlap(OtherActor);
}

void ABaseProjectile::HandleProjectileCollision(const AActor* OtherActor)
{
	switch (ProjectileVsProjectilePolicy)
	 {
	 case EProjectileVsProjectilePolicy::Ignore:
	 	return;
	
	 case EProjectileVsProjectilePolicy::DestroySelf:
	 	HandleImpactEffects();
	 	if (HasAuthority()) Destroy();
	 	return;
	
	 case EProjectileVsProjectilePolicy::BounceOff:
	 	Bounce(OtherActor->GetActorLocation());
	 	return;
	 }
}

void ABaseProjectile::SimpleDealDamageAndDestroy(AActor* OtherActor)
{
	SimpleDealDamage(OtherActor);

	if (HasAuthority() && ShouldDestroy())
	{
		Destroy();
	}
}

void ABaseProjectile::SimpleDealDamage(AActor* OtherActor)
{
	HandleImpactEffects();

	if (HasAuthority())
	{
		if (CheckForEffectTarget(OtherActor))
			ApplyDamageEffect(OtherActor);
	}
}

void ABaseProjectile::ApplyDamageEffect(AActor* OtherActor) const
{
	if (!HasAuthority()) return;

	SpellParams->ActorHit = OtherActor;
	
	UObject* Receiver = OtherActor->GetClass()->ImplementsInterface(UPWEffectReceiverInterface::StaticClass())? IPWEffectReceiverInterface::Execute_GetEffectReceiver(OtherActor) : OtherActor;
	if (Receiver && Receiver->GetClass()->ImplementsInterface(UDamageable::StaticClass()))
		IDamageable::Execute_ApplyDamage(Receiver, SpellParams);
	
	if (Receiver && Receiver->GetClass()->ImplementsInterface(UEffectable::StaticClass()))
		IEffectable::Execute_ApplyEffects(Receiver, SpellParams);
}

void ABaseProjectile::HandleImpactEffects()
{
	if (HasAuthority())
		MulticastPlayImpactEffects();
	else
		PlayImpactEffects();
}

void ABaseProjectile::PlayImpactEffects()
{
	if (bHitEffectsPlayed) return;
	bHitEffectsPlayed = true;

	if (ImpactSound) UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, GetActorLocation(), FRotator::ZeroRotator);
	if (ImpactEffect) UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ImpactEffect, GetActorLocation(), GetActorRotation());

	if (ShouldDestroy() && LoopingSound)
	{
		LoopingSound->Stop();
		LoopingSound->DestroyComponent();
	}
}

void ABaseProjectile::MulticastPlayImpactEffects_Implementation()
{
	PlayImpactEffects();
}

void ABaseProjectile::Bounce(const FVector PointOfOrigin) const
{
	ProjectileMovement->Velocity = CalculateBounceVelocity(PointOfOrigin, ProjectileMovement->Velocity);
	ProjectileMovement->UpdateComponentVelocity();
}

void ABaseProjectile::ResetSpell()
{
	Super::ResetSpell();

	bHitEffectsPlayed = false;
	LastHitActor = nullptr;
	LastHitTimes.Empty();
	HitCount = 0;
}

FVector ABaseProjectile::CalculateBounceVelocity(const FVector PointOfOrigin, const FVector Velocity) const
{
	FVector SphereOrigin = PointOfOrigin;
	SphereOrigin.Z = GetActorLocation().Z;
	const FVector Normal = (GetActorLocation() - SphereOrigin).GetSafeNormal();
	const FVector ReflectedVelocity = FMath::GetReflectionVector(Velocity, Normal);
	return ReflectedVelocity;
}
