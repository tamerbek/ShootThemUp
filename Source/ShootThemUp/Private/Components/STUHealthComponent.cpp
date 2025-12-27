// Shoot Them Up


#include "Components/STUHealthComponent.h"
#include "Engine/DamageEvents.h"
#include "Dev/STUFireDamageType.h"
#include "Dev/STUIceDamageType.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All)

// Sets default values for this component's properties
USTUHealthComponent::USTUHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void USTUHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	OnHealthChanged.Broadcast(Health);

	AActor* ComponentOwner = GetOwner();
	if (ComponentOwner)
	{
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USTUHealthComponent::OnTakeAnyDamage);
	}
	
}

void USTUHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.0f || IsDead()) return;
	Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);
	OnHealthChanged.Broadcast(Health);
	UE_LOG(LogHealthComponent, Display, TEXT("Damage: %f"), Damage);
	
	if (IsDead())
	{
		EventOnDeath.Broadcast();
	}

	if (DamageType)
	{
		if (DamageType->IsA<USTUFireDamageType>())
		{
			UE_LOG(LogHealthComponent, Display, TEXT("FIRE DAMAGE"));
		}
		else if (DamageType->IsA<USTUIceDamageType>())
		{
			UE_LOG(LogHealthComponent, Display, TEXT("ICE DAMAGE"));
		}
	}
}