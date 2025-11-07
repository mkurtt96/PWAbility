// copyright mkurtt96


#include "Library/AbilityActorHelperFunctions.h"

#include "NiagaraComponent.h"

void UAbilityActorHelperFunctions::CascadedDestroy(UPrimitiveComponent* CollisionComponent, UNiagaraComponent* ProjectileNiagara, float Delay)
{
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ProjectileNiagara->Deactivate();
	ProjectileNiagara->SetAutoDestroy(true);
	FTimerHandle TimerHandle;
	ProjectileNiagara->GetOwner()->GetWorldTimerManager().SetTimer(TimerHandle, [ProjectileNiagara]()
	{
		ProjectileNiagara->GetOwner()->Destroy();
	}, Delay, false);
}
