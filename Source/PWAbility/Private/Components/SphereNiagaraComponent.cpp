// copyright Iompa


#include "Components/SphereNiagaraComponent.h"

#include "NiagaraComponent.h"
#include "Components/SphereComponent.h"


USphereNiagaraComponent::USphereNiagaraComponent()
{
	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
	NiagaraComponent->SetupAttachment(this);

	BlockComponent = CreateDefaultSubobject<USphereComponent>(TEXT("BlockComponent"));
	BlockComponent->SetupAttachment(this);

	OverlapComponent = CreateDefaultSubobject<USphereComponent>(TEXT("OverlapComponent"));
	OverlapComponent->SetupAttachment(this);
}