// Shoot Them Up

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUBaseWeapon.generated.h"

class USkeletalMeshComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASTUBaseWeapon();

	virtual void StartFire();
	virtual void StopFire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FName MuzzleSocketName = "Muzzle";

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float ShootTraceMaxDistance = 10000.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float DamageAmount = 10.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float TimeBetweenShots = 0.1f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float BulletSpread = 1.5f;

	void MakeShot();

	APlayerController* GetPlayerController() const;

	void MakeDamage(const FHitResult& HitResult);

	

public:	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USkeletalMeshComponent* WeaponMesh;

private:
	FTimerHandle ShotTimerHandle;
};
