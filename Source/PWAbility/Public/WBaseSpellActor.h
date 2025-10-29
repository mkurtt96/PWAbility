// copyright Iompa

#pragma once

#include "CoreMinimal.h"
#include "Ability/PWSpellParamsInterface.h"
#include "GameFramework/Actor.h"
#include "WBaseSpellActor.generated.h"

class USpellParams;
enum EPrecastDecalType : uint8;

UCLASS()
class PWABILITY_API AWBaseSpellActor : public AActor, public IPWSpellParamsInterface
{
	GENERATED_BODY()

public:
	AWBaseSpellActor();
	virtual void BeginPlay() override;
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable, Category = "Projectile|Functions")
	virtual void ResetSpell();
	
	// UFUNCTION()
	// void OnGamePhaseChanged(EGamePhase NewPhase);
	
	UPROPERTY(BlueprintReadWrite, Replicated)
	USpellParams* SpellParams;

	virtual void SetSpellParams_Implementation(USpellParams* Params) override;
	
protected:
	//Target
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "BaseSpell|Target")
	virtual bool CheckForCollisionTarget(const AActor* OtherActor) const;
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "BaseSpell|Target")
	virtual bool CheckForEffectTarget(const AActor* OtherActor) const;
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "BaseSpell|Target")
	virtual bool IsSelf(const AActor* OtherActor) const;
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "BaseSpell|Target")
	virtual bool IsEnemy(const AActor* OtherActor) const;
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "BaseSpell|Target")
	virtual bool IsAlly(const AActor* OtherActor) const;
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "BaseSpell|Target")
	static bool IsActorProjectile(const AActor* OtherActor);
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "BaseSpell|Target")
	static bool IsNoCollision(const AActor* OtherActor);
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "BaseSpell|Target")
	static bool IsDontTriggerCollision(const AActor* OtherActor);
	

private:

public:
};
