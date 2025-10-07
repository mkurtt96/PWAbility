// copyright MGK


#include "MyEffectActor.h"

#include "AbilityEnums.h"

AMyEffectActor::AMyEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneComponent"));
}

void AMyEffectActor::BeginPlay()
{
	Super::BeginPlay();
}

void AMyEffectActor::ApplyEffectToTarget(AActor* TargetActor, FEffectData EffectData)
{
	// if (TargetActor->ActorHasTag(FName("Enemy")) && !bApplyEffectToEnemies) return;
	//
	// UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	// if (!TargetASC) return;
	// check(EffectData.GameplayEffectClass)
	//
	// FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
	// EffectContextHandle.AddSourceObject(this);
	// const FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(
	// 	EffectData.GameplayEffectClass, ActorLevel, EffectContextHandle);
	// const FActiveGameplayEffectHandle ActiveEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(
	// 	*EffectSpecHandle.Data.Get());
	//
	// const bool bIsInfinite = EffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;
	// if (bIsInfinite && EffectData.EffectRemovalPolicy != EEffectRemovalPolicy::DoNotRemove)
	// {
	// 	ActiveEffectHandles.Add(ActiveEffectHandle, TargetASC);
	// }
	//
	// if (!bIsInfinite && bDestroyOnEffectApplication)
	// {
	// 	Destroy();
	// }
}

void AMyEffectActor::RemoveEffectFromTarget(AActor* TargetActor)
{
	// UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	// if (!IsValid(TargetASC)) return;
	//
	// TArray<FActiveGameplayEffectHandle> HandlesToRemove;
	// for (auto HandlePair : ActiveEffectHandles)
	// {
	// 	if (TargetASC == HandlePair.Value)
	// 	{
	// 		TargetASC->RemoveActiveGameplayEffect(HandlePair.Key, 1);
	// 		HandlesToRemove.Add(HandlePair.Key);
	// 	}
	// }
	// 	
	// for (auto& Handle : HandlesToRemove)
	// {
	// 	ActiveEffectHandles.FindAndRemoveChecked(Handle);
	// }
}

void AMyEffectActor::OnOverlap(AActor* TargetActor)
{
	if (TargetActor->ActorHasTag(FName("Enemy")) && !bApplyEffectToEnemies) return;
	
	for (FEffectData Effect : Effects)
	{
		if (Effect.EffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
		{
			ApplyEffectToTarget(TargetActor,Effect);
		}
	}
}

void AMyEffectActor::OnEndOverlap(AActor* TargetActor)
{
	if (TargetActor->ActorHasTag(FName("Enemy")) && !bApplyEffectToEnemies) return;
	
	for (FEffectData Effect : Effects)
	{
		if (Effect.EffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
		{
			ApplyEffectToTarget(TargetActor,Effect);
		}
	}

	for (FEffectData Effect : Effects)
	{
		if (Effect.EffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
		{
			RemoveEffectFromTarget(TargetActor);
		}
	}
}
