// copyright mkurtt96

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AbilityActorHelperFunctions.generated.h"

class UNiagaraComponent;
/**
 * 
 */
UCLASS()
class PWABILITY_API UAbilityActorHelperFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "AbilityActor")
	static void CascadedDestroy(UPrimitiveComponent* CollisionComponent, UNiagaraComponent* ProjectileNiagara, float Delay = 0);
};
