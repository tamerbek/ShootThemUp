// Shoot Them Up


#include "Weapons/STURifleWeapon.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

void ASTURifleWeapon::StartFire() {
	MakeShot();
	GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ASTURifleWeapon::MakeShot, TimeBetweenShots, true);
}

void ASTURifleWeapon::StopFire() {
	GetWorldTimerManager().ClearTimer(ShotTimerHandle);
}

void ASTURifleWeapon::MakeShot() {
	if (!GetWorld() || IsAmmoEmpty())
	{
		StopFire();
		return;
	}

	const auto Controller = GetPlayerController();
	if (!Controller) return;

	FVector TraceStart, TraceEnd;
	if (!GetTraceData(TraceStart, TraceEnd))
	{
		StopFire();
		return;
	}

	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);

	if (HitResult.bBlockingHit)
	{
		MakeDamage(HitResult);
		DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), HitResult.ImpactPoint, FColor::Red, false, 3.0f, 0, 3.0f);
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 10.0f, FColor::Red, false, 5.0f);
		//UE_LOG(BaseWeaponLog, Display, TEXT("Hit Bone: %s"), *HitResult.BoneName.ToString());
	}
	else {
		DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), TraceEnd, FColor::Red, false, 3.0f, 0, 3.0f);
	}

	DecreaseAmmo();
}

bool ASTURifleWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	FVector ViewLocation;
	FRotator ViewRotation;
	if (!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;

	TraceStart = ViewLocation;
	const auto HalfRad = FMath::DegreesToRadians(BulletSpread);
	const FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(), HalfRad);
	TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
	return true;
}