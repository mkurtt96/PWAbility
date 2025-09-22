// copyright MGK

#pragma once

#include "CoreMinimal.h"
#include "AbilityEnums.h"
#include "GameFramework/Actor.h"
#include "MyEffectActor.generated.h"

class UAbilitySystemComponent;
class UGameplayEffect;

USTRUCT(BlueprintType)
struct FEffectData
{
	GENERATED_BODY()
public:
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//TSubclassOf<UGameplayEffect> GameplayEffectClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEffectApplicationPolicy EffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEffectRemovalPolicy EffectRemovalPolicy = EEffectRemovalPolicy::DoNotRemove;
};

UCLASS()
class PWABILITY_API AMyEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AMyEffectActor();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor, FEffectData GameplayEffectClass);
	void RemoveEffectFromTarget(AActor* TargetActor);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Effects")
	bool bDestroyOnEffectApplication = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Effects")
	bool bApplyEffectToEnemies = false;

	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor* TargetActor);
	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* TargetActor);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Effects")
	TArray<FEffectData> Effects;
	
	//TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> ActiveEffectHandles;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Effects")
	float ActorLevel = 1.f; 
private:

};
