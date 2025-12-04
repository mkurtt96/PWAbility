// copyright Iompa

#pragma once

#include "CoreMinimal.h"
#include "AbilityEnums.h"
#include "WBaseSpellActor.h"
#include "Ability/SpellParams.h"
#include "GameFramework/Actor.h"
#include "Interface/Projectile.h"
#include "BaseProjectile.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnProjectileOverlapDelegate, AActor*, OtherActor);

class UWProjectileMovementComponent;
class UNiagaraSystem;
class USphereComponent;

UCLASS(Blueprintable,BlueprintType)
class PWABILITY_API ABaseProjectile : public AWBaseSpellActor, public IProjectile
{
	GENERATED_BODY()

public: // ---- PROPERTIES
	UFUNCTION(BlueprintImplementableEvent, Category = "Projectile")
	void OnProjectileOverlap(AActor* OtherActor);
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile|Movement")
	TObjectPtr<UWProjectileMovementComponent> ProjectileMovement;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USphereComponent> Sphere;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Projectile|Data")
	AActor* LastHitActor = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = "Projectile|Data")
	int32 HitCount = 0;
	UPROPERTY(BlueprintReadOnly, Category = "Projectile|Data")
	float LastHitTime = -99999;
	UPROPERTY(BlueprintReadOnly, Category = "Projectile|Data")
	TMap<AActor*, float> LastHitTimes;
	UPROPERTY(BlueprintReadWrite, Category = "Projectile|Data")
	bool bHitEffectsPlayed = false;
	
	UPROPERTY(EditAnywhere, Category = "Projectile")
	int8 DestroyOnHit = 1;
	UPROPERTY(EditAnywhere, Category = "Projectile")
	bool bCanHitTheSameTarget = false;
	UPROPERTY(EditAnywhere, Category = "Projectile")
	float TargetHitCooldown = .2f;

private:
	UPROPERTY(EditAnywhere, Category = "Projectile")
	EProjectileVsProjectilePolicy ProjectileVsProjectilePolicy = EProjectileVsProjectilePolicy::DestroySelf;
	UPROPERTY(EditAnywhere, Category = "Projectile|Effects")
	TObjectPtr<UNiagaraSystem> ImpactEffect;
	UPROPERTY(EditAnywhere, Category = "Projectile|Effects")
	TObjectPtr<USoundBase> ImpactSound;
	UPROPERTY(EditAnywhere, Category = "Projectile|Effects")
	TObjectPtr<USoundBase> ActiveSoundLoop;
	UPROPERTY()
	TObjectPtr<UAudioComponent> LoopingSound;
	
public: // ---- FUNCTIONS
	ABaseProjectile();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Projectile")
	void Reflect(AActor* ActorReflectedBy);

	UFUNCTION(BlueprintCallable, Category = "Projectile|Functions")
	virtual void Bounce(const FVector PointOfOrigin) const;

	virtual void ResetSpell() override;
protected:
	virtual void BeginPlay() override;
	virtual void Destroyed() override;

	UFUNCTION()
	virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	//Effects
	UFUNCTION(BlueprintCallable, Category = "Projectile|Effects")
	virtual void ApplyEffects(AActor* OtherActor) const; //server only
	
	//Impact Effects
	UFUNCTION(BlueprintCallable, Category = "Projectile|Effects")
	virtual void HandleImpactEffects();
	virtual void PlayImpactEffects();
	UFUNCTION(NetMulticast, Reliable)
	virtual void MulticastPlayImpactEffects();
	
	/** Predefined Hit Logic. Ideally should be called on Hit. Will Destroy on Projectile Hit.
	 * Handles Impact Effects. Applies Damage Effect if ShouldApplyEffect. And Destroy if ShouldDestroy. */
	UFUNCTION(BlueprintCallable)
	virtual void SimpleApplyEffectsAndDestroy(AActor* OtherActor);
	
	/** Deal Damage.
	 *Handles Impact Effects. Applies Damage Effect if ShouldApplyEffect.*/
	UFUNCTION(BlueprintCallable)
	virtual void SimpleApplyEffects (AActor* OtherActor);

	UFUNCTION(BlueprintCallable, Category = "Projectile|Data")
	FORCEINLINE bool IsANewTarget(const AActor* OtherActor) const { return LastHitActor != OtherActor; }

	FVector CalculateBounceVelocity(const FVector PointOfOrigin, const FVector Velocity) const;
	
	virtual bool CanHitTarget(const AActor* OtherActor);
	FORCEINLINE virtual bool ShouldDestroy() const { return HitCount == DestroyOnHit; }
	virtual void HandleProjectileCollision(const AActor* OtherActor);
	virtual bool ShouldIgnoreOverlap(const AActor* OtherActor) const;
private:

public: // GETTERS
	UWProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }
	UFUNCTION(BlueprintImplementableEvent, BlueprintPure, Category = "Projectile|Data")
	float CalculateLifeTime();

};