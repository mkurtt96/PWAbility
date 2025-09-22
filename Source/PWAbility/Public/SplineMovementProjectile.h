// copyright Iompa

#pragma once

#include "CoreMinimal.h"
#include "BaseProjectile.h"
#include "SplineMovementProjectile.generated.h"

class USplineComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSplinePathCompleteDelegate);

UCLASS(BlueprintType, Blueprintable)
class PWABILITY_API ASplineMovementProjectile : public ABaseProjectile
{
	GENERATED_BODY()

public:
	ASplineMovementProjectile();

	UPROPERTY(BlueprintAssignable)
	FSplinePathCompleteDelegate OnSplinePathComplete;

	UFUNCTION(BlueprintCallable)
	void EndSplineMovement(bool ContinueMovement);
	UFUNCTION(BlueprintImplementableEvent)
	void SplineMovementEnded();
	UFUNCTION(BlueprintCallable)
	void EndSplineMovementWithBounce(const FVector PointOfOrigin);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	virtual void Destroyed() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile|Movement")
	USplineComponent* SplineComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	bool DestroyOnPathComplete = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile|Movement")
	FRuntimeFloatCurve CustomProjectileSpeedMultiplier;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile|Movement")
	float MinimumRangeMultiplier = .5;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile|Movement")
	bool bUpdateRotation = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile|Movement")
	float DistanceTravelled = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile|Movement")
	float SpeedScaleFactor = 0;

	bool bIsPathComplete = false;
	bool bIsSplineStopped = false;

	UPROPERTY(BlueprintReadWrite, Category = "Projectile|Movement")
	bool bIsReflected = false;

private:

public:
};
