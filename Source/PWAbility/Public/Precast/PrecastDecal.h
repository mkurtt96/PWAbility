// copyright Iompa

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PrecastDecal.generated.h"

UCLASS()
class PWABILITY_API APrecastDecal : public AActor
{
	GENERATED_BODY()

public:
	APrecastDecal();
	
	void SetRadius(float Radius) const;
	void SetLineEndpoints(const FVector& Start, const FVector& End, const float Range) const;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UDecalComponent> DecalComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInstanceDynamic* DecalMaterialInstance;
};
