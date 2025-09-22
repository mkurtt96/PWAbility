// copyright Iompa

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "SphereNiagaraComponent.generated.h"

class USphereComponent;
class UNiagaraComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), BlueprintType, Blueprintable)
class PWABILITY_API USphereNiagaraComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	USphereNiagaraComponent();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UNiagaraComponent> NiagaraComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<USphereComponent> BlockComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<USphereComponent> OverlapComponent;

public:
};
