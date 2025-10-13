// copyright mkurtt96


#include "WBaseSpellActor.h"
 
#include "Ability/SpellParams.h"
#include "Interface/Projectile.h"
#include "Net/UnrealNetwork.h"

#if WITH_PWTEAMS
#include "TeamFunctions.h"
#endif

AWBaseSpellActor::AWBaseSpellActor(): SpellParams(nullptr)
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	AActor::SetReplicateMovement(true);
}

void AWBaseSpellActor::BeginPlay()
{
	Super::BeginPlay();
	
	// AMyGameState* MyGameState = Cast<AMyGameState>(UGameplayStatics::GetGameState(this));
	// MyGameState->OnGamePhaseChanged.AddDynamic(this, &AWBaseSpellActor::OnGamePhaseChanged);
}

void AWBaseSpellActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME_CONDITION(AWBaseSpellActor, SpellParams, COND_InitialOnly);
}

void AWBaseSpellActor::ResetSpell()
{
}

// void AWBaseSpellActor::OnGamePhaseChanged(EGamePhase NewPhase)
// {
// 	Destroy();
// }

void AWBaseSpellActor::SetSpellParams_Implementation(USpellParamsBase* Params)
{
	SpellParams = Params;
}

bool AWBaseSpellActor::CheckForCollisionTarget(const AActor* OtherActor) const
{
	
#if WITH_PWTEAMS
	return UTeamFunctions::MatchesMask(SpellParams->SourceAvatar, OtherActor, SpellParams->TargetCollisionMask);
#else
	return false;
#endif
}

bool AWBaseSpellActor::CheckForEffectTarget(const AActor* OtherActor) const
{
#if WITH_PWTEAMS
	return UTeamFunctions::MatchesMask(SpellParams->SourceAvatar, OtherActor, SpellParams->TargetEffectMask);
#else
	return false;
#endif
}

bool AWBaseSpellActor::IsSelf(const AActor* OtherActor) const
{
#if WITH_PWTEAMS
	return UTeamFunctions::GetRelation(SpellParams->SourceAvatar, OtherActor) == ERelation::Self;
#else
	return false;
#endif
}

bool AWBaseSpellActor::IsEnemy(const AActor* OtherActor) const
{
#if WITH_PWTEAMS
	return UTeamFunctions::GetRelation(SpellParams->SourceAvatar, OtherActor) == ERelation::Enemy;
#else
	return false;
#endif
}

bool AWBaseSpellActor::IsAlly(const AActor* OtherActor) const
{
#if WITH_PWTEAMS
	return UTeamFunctions::GetRelation(SpellParams->SourceAvatar, OtherActor) == ERelation::Ally;
#else
	return false;
#endif
}

bool AWBaseSpellActor::IsActorProjectile(const AActor* OtherActor)
{
	return OtherActor->Implements<UProjectile>();
}

bool AWBaseSpellActor::IsNoCollision(const AActor* OtherActor)
{
	return OtherActor->Implements<UNoCollision>();
}

bool AWBaseSpellActor::IsDontTriggerCollision(const AActor* OtherActor)
{
	return OtherActor->Implements<UDontTriggerCollision>();
}


