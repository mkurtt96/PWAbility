// copyright Iompa

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "WProjectileMovementComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PWABILITY_API UWProjectileMovementComponent : public UProjectileMovementComponent
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintPure, Category = "ProjectileMovementComponent")
	FVector GetHomingTargetLocation() const;
	UFUNCTION(BlueprintPure, Category = "ProjectileMovementComponent")
	AActor* GetHomingTargetActor() const;
	UFUNCTION(BlueprintCallable, Category = "ProjectileMovementComponent")
	void SetHomingTargetLocation(const FVector& TargetLocation);
	UFUNCTION(BlueprintCallable, Category = "ProjectileMovementComponent")
	void SetHomingTargetActor(AActor* TargetActor);

	UFUNCTION(BlueprintCallable, Category = "ProjectileMovementComponent")
	void AddVelocity(const FVector& Force);
	

protected:
	UPROPERTY()
	FVector HomingTargetLocation = FVector::ZeroVector;
	UPROPERTY()
	AActor* HomingTargetActor = nullptr;
};
