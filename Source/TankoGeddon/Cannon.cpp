// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannon.h"
#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components\SceneComponent.h"
#include "Projectile.h"
#include "DrawDebugHelpers.h"

// Sets default values
ACannon::ACannon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* CannonSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("CannonRoot"));
	RootComponent = CannonSceneComponent;

	CannonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CannonMesh"));
	CannonMesh->SetupAttachment(CannonSceneComponent);

	ProjectileSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("ProjectileSpawnPoint"));
	ProjectileSpawnPoint->SetupAttachment(CannonSceneComponent);
}

void ACannon::Fire()
{
	//cannon fire test
	if (!bCanFire)
	{
		GEngine->AddOnScreenDebugMessage(10, 1, FColor::Red, "Reload");
		return;
	}
	if (WhizBang <= 0)
	{
		GEngine->AddOnScreenDebugMessage(10, 1, FColor::Red, "Reload");
		return;
	}
	
	bCanFire = false;
	

	if (CannonType == ECannonType::FireProjectile)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Fire projectile ")));
		//Projectile firing implementation
		AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnPoint->GetComponentLocation(), ProjectileSpawnPoint->GetComponentRotation());
		WhizBang--;
		if (projectile)
		{
			projectile->Start();
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Fire trace ")));
		FHitResult hitResult;
		FCollisionQueryParams traceParams = FCollisionQueryParams(FName(TEXT("FireTrace")), true, this);
		traceParams.bTraceComplex = true;
		traceParams.bReturnPhysicalMaterial = false;

		FVector StartTrace = ProjectileSpawnPoint->GetComponentLocation();
		FVector EndTrace = StartTrace + ProjectileSpawnPoint->GetForwardVector() * FireRange;

		if (GetWorld()->LineTraceSingleByChannel(hitResult, StartTrace, EndTrace, ECollisionChannel::ECC_Visibility, traceParams))
		{
			DrawDebugLine(GetWorld(), StartTrace, hitResult.Location, FColor::Red, false, 0.5f, 0, 10);
			if (hitResult.GetActor())
			{
				hitResult.GetActor()->Destroy();
			}
		}
		else
		{
			DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Purple, false, 0.5f, 0, 10);
		}
		WhizBang--;

	}
	GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &ACannon::Reload, ReloadTime, false);
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Bullet = %d"), WhizBang));
	
}

void ACannon::FireSpecial()
{

	if (!bCanFire || WhizBang <= 0)
	{

		GEngine->AddOnScreenDebugMessage(10, 1, FColor::Red, "Not bullet");
		return;
	}

	bCanFire = false;

	Bang();
}
void ACannon::Reload()
{
	bCanFire = true;
}
void ACannon::Bang()
{
	if (ActualBang == BangSize)
	{
		AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnPoint->GetComponentLocation(), ProjectileSpawnPoint->GetComponentRotation());
		if (projectile)
		{
			if (WhizBang > 0)
				projectile->Start();
		}
		GetWorld()->GetTimerManager().ClearTimer(BangTimer);
		bCanFire = true;
		ActualBang = 0;
		WhizBang--;
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Bullet = %d"), WhizBang));
		return;
	}
	ActualBang++;
	if (CannonType == ECannonType::FireProjectile)
	{
		
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Purple, FString::Printf(TEXT("Fire Projectile")));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Purple, FString::Printf(TEXT("Fire trace")));
	}
	GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &ACannon::Reload, BangInterval, false);
}






