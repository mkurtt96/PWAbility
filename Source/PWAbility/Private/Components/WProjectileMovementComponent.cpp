// copyright Iompa


#include "Components/WProjectileMovementComponent.h"


FVector UWProjectileMovementComponent::GetHomingTargetLocation() const
{
	return HomingTargetLocation;
}

AActor* UWProjectileMovementComponent::GetHomingTargetActor() const
{
	return HomingTargetActor;
}

void UWProjectileMovementComponent::SetHomingTargetLocation(const FVector& TargetLocation)
{
	USceneComponent* HomingTarget = NewObject<USceneComponent>(USceneComponent::StaticClass());
	HomingTarget->SetWorldLocation(TargetLocation);
	HomingTargetComponent = HomingTarget;
	HomingTargetLocation = TargetLocation;
}

void UWProjectileMovementComponent::SetHomingTargetActor(AActor* TargetActor)
{
	USceneComponent* HomingTarget = nullptr;
	if (TargetActor)
		HomingTarget = TargetActor->GetRootComponent();
	HomingTargetComponent = HomingTarget;
	HomingTargetActor = TargetActor;
}

void UWProjectileMovementComponent::AddVelocity(const FVector& DeltaForce)
{
	Velocity += DeltaForce;

	SetVelocityInLocalSpace(Velocity);
}
