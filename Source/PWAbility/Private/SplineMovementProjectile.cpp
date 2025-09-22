// copyright Iompa


#include "SplineMovementProjectile.h"

#include "Ability/SpellParams.h"
#include "Components/WProjectileMovementComponent.h"
#include "Components/SplineComponent.h"


ASplineMovementProjectile::ASplineMovementProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	SplineComponent->SetupAttachment(RootComponent);
}

void ASplineMovementProjectile::EndSplineMovement(const bool ContinueMovement)
{
	bIsSplineStopped = true;
	if (ContinueMovement)
	{
		if (ProjectileMovement->IsActive()) return;
		ProjectileMovement->Activate();
		const FRichCurve* RC = CustomProjectileSpeedMultiplier.GetRichCurveConst();
		const float SpeedMultiplier = RC->Eval(DistanceTravelled / SplineComponent->GetSplineLength(), 1.f);
		ProjectileMovement->Velocity = GetActorForwardVector() * SpellParams->More->GetFloat("Speed") * SpeedMultiplier;
	}

	SplineMovementEnded();
}

void ASplineMovementProjectile::EndSplineMovementWithBounce(const FVector PointOfOrigin)
{
	bIsSplineStopped = true;
	ProjectileMovement->Activate();
	const FRichCurve* RC = CustomProjectileSpeedMultiplier.GetRichCurveConst();
	const float SpeedMultiplier = RC->Eval(DistanceTravelled / SplineComponent->GetSplineLength(), 1.f);
	const FVector Velocity = GetActorForwardVector() * SpellParams->More->GetFloat("Speed") * SpeedMultiplier;

	ProjectileMovement->Velocity = CalculateBounceVelocity(PointOfOrigin, Velocity);
	ProjectileMovement->UpdateComponentVelocity();
	
	SplineMovementEnded();
}

void ASplineMovementProjectile::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		const float Dist = FVector::Dist(SpellParams->More->GetVector("TargetLocation"), GetActorLocation());
		const float ClampedDist = FMath::Clamp(Dist, SpellParams->More->GetFloat("Range") * MinimumRangeMultiplier, SpellParams->More->GetFloat("Range"));

		const float NewScale = ClampedDist / 1000;
		SplineComponent->SetRelativeScale3D(FVector(NewScale, NewScale, NewScale));

		SpeedScaleFactor = 1.0f / NewScale;

		SetLifeSpan(0);
		SplineComponent->Duration = CalculateLifeTime();

		SplineComponent->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);

		FVector::Dist(SpellParams->More->GetVector("TargetLocation"), GetActorLocation());
	}
}

void ASplineMovementProjectile::Tick(const float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);


	if (HasAuthority())
	{
		if (bIsReflected && !bIsPathComplete)
		{
			DistanceTravelled += SpellParams->More->GetFloat("Speed") * SpeedScaleFactor * CustomProjectileSpeedMultiplier.GetValueAtLevel(DistanceTravelled / SplineComponent->GetSplineLength()) * DeltaSeconds;

			if (DistanceTravelled >= SplineComponent->GetSplineLength())
			{
				if (DestroyOnPathComplete)
					Destroy();
			}
		}
		else if (!bIsSplineStopped)
		{
			DistanceTravelled += SpellParams->More->GetFloat("Speed") * SpeedScaleFactor * CustomProjectileSpeedMultiplier.GetValueAtLevel(DistanceTravelled / SplineComponent->GetSplineLength()) * DeltaSeconds;

			const FVector Location = SplineComponent->GetLocationAtDistanceAlongSpline(DistanceTravelled, ESplineCoordinateSpace::World);
			SetActorLocation(Location);

			if (DistanceTravelled >= SplineComponent->GetSplineLength())
			{
				bIsPathComplete = true;
				bIsSplineStopped = true;
				OnSplinePathComplete.Broadcast();

				if (DestroyOnPathComplete)
					Destroy();
			}

			if (bUpdateRotation)
			{
				const FRotator Rotation = SplineComponent->GetRotationAtDistanceAlongSpline(DistanceTravelled, ESplineCoordinateSpace::World);
				SetActorRotation(Rotation);
			}
		}
	}
}

void ASplineMovementProjectile::Destroyed()
{
	Super::Destroyed();

	SplineComponent->DestroyComponent();
}
