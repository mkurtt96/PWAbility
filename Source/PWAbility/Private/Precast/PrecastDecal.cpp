// copyright Iompa


#include "Precast/PrecastDecal.h"

#include "Components/DecalComponent.h"
#include "Kismet/KismetMathLibrary.h"


APrecastDecal::APrecastDecal()
{
	DecalComponent = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalComponent"));
	DecalComponent->SetupAttachment(GetRootComponent());
}

void APrecastDecal::SetRadius(const float Radius) const
{
	DecalComponent->DecalSize = FVector(30, Radius, Radius);
}

void APrecastDecal::SetLineEndpoints(const FVector& Start, const FVector& End, const float Range) const
{
	if (DecalMaterialInstance)
	{
	 	DecalMaterialInstance->SetVectorParameterValue(TEXT("StartPoint"), Start);
	 	DecalMaterialInstance->SetVectorParameterValue(TEXT("EndPoint"), End);
	}

	FVector Direction = (End - Start).GetSafeNormal();

	FVector NewStart = Start + Direction * 100.0f;
	FVector NewEnd = NewStart + Direction * Range;
	
	FVector Midpoint = (NewStart + NewEnd) / 2.0f;

	FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(NewStart, NewEnd);

	FVector Size = FVector(Range / 2, DecalComponent->DecalSize.Y, 30);

	DecalComponent->SetWorldLocation(Midpoint);
	DecalComponent->SetWorldRotation(Rotation);
	DecalComponent->DecalSize = Size;
}