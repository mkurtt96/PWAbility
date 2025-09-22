// copyright Iompa

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Projectile.generated.h"

UINTERFACE()
class UProjectile : public UInterface
{
	GENERATED_BODY()
};

class PWABILITY_API IProjectile
{
	GENERATED_BODY()
};

UINTERFACE()
class UNoCollision : public UInterface
{
	GENERATED_BODY()
};

class PWABILITY_API INoCollision 
{
	GENERATED_BODY()
};

UINTERFACE()
class UDontTriggerCollision : public UInterface
{
	GENERATED_BODY()
};

class PWABILITY_API IDontTriggerCollision
{
	GENERATED_BODY()
};