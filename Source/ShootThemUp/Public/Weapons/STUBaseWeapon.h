// Shoot Them Up

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUBaseWeapon.generated.h"

class USkeletalMeshComponent;

USTRUCT(BlueprintType)
struct FAmmoData
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "Weapon")
	int32 Bullets;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "Weapon", meta = (EditCondition = "!Infinite"))
	int32 Clips;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "Weapon")
	bool Infinite;
};

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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FName MuzzleSocketName = "Muzzle";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float TraceMaxDistance = 10000.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float DamageAmount = 10.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FAmmoData DefaultAmmo{ 15, 10, true };

	virtual void MakeShot();
	virtual void MakeHit(FHitResult HitResult, FVector TraceStart, FVector TraceEnd);
	bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;
	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;
	FVector GetMuzzleWorldLocation() const;

	APlayerController* GetPlayerController() const;

	void MakeDamage(const FHitResult& HitResult);

	void DecreaseAmmo();
	bool IsAmmoEmpty() const;
	bool IsClipEmpty() const;
	void ChangeClip();
	void LogAmmo();


private:
	FAmmoData CurrentAmmo;

};
