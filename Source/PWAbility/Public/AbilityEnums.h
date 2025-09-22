// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "AbilityEnums.generated.h"

UENUM(BlueprintType)
enum class EProjectileVsProjectilePolicy : uint8
{
	Ignore,
	DestroySelf,
	BounceOff
};

UENUM(BlueprintType)
enum class EEffectApplicationPolicy : uint8
{
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	DoNotApply
};

UENUM(BlueprintType)
enum class EEffectRemovalPolicy : uint8
{
	RemoveOnEndOverlap,
	DoNotRemove
};


/**
 * 
 */
UCLASS()
class PWABILITY_API UAbilityEnums : public UObject
{
	GENERATED_BODY()
};
