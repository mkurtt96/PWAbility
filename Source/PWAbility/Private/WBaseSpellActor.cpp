// copyright mkurtt96


#include "WBaseSpellActor.h"

#include "TeamFunctions.h"
#include "Ability/SpellParams.h"
#include "Interface/Projectile.h"
#include "Net/UnrealNetwork.h"

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

bool AWBaseSpellActor::CheckForCollisionTarget(const AActor* OtherActor) const
{
	return UTeamFunctions::MatchesMask(SpellParams->SourceAvatar, OtherActor, SpellParams->TargetCollisionTypes);
}

bool AWBaseSpellActor::CheckForEffectTarget(const AActor* OtherActor) const
{
	return UTeamFunctions::MatchesMask(SpellParams->SourceAvatar, OtherActor, SpellParams->TargetEffectTypes);
}

bool AWBaseSpellActor::IsSelf(const AActor* OtherActor) const
{
	return UTeamFunctions::GetRelation(SpellParams->SourceAvatar, OtherActor) == ERelation::Self;
}

bool AWBaseSpellActor::IsEnemy(const AActor* OtherActor) const
{
	return UTeamFunctions::GetRelation(SpellParams->SourceAvatar, OtherActor) == ERelation::Enemy;
}

bool AWBaseSpellActor::IsAlly(const AActor* OtherActor) const
{
	return UTeamFunctions::GetRelation(SpellParams->SourceAvatar, OtherActor) == ERelation::Ally;
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


