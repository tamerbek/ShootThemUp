// Shoot Them Up

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUHealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FEventOnDeath);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHEMUP_API USTUHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USTUHealthComponent();

	FEventOnDeath EventOnDeath;
	FOnHealthChanged OnHealthChanged;
	
	float GetHealth() const { return Health; }

	UFUNCTION(BlueprintCallable)
	bool IsDead() const { return FMath::IsNearlyZero(Health); }
		

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0.0", ClampMax = "200.0"))
	float MaxHealth = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AutoHealt")
	bool Autoheal = true;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AutoHealt", meta = (EditCondition = "Autoheal"))
	float HealtUpdateTime = 0.3f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AutoHealt", meta = (EditCondition = "Autoheal"))
	float HealDelay = 3.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AutoHealt", meta = (EditCondition = "Autoheal"))
	float HealModifier = 1.0f;

private:
	float Health = 0.0f;
	FTimerHandle HealTimerHandle;

	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION()
	void HealUpdate();
	
	void SetHealth(float NewHealth);
};