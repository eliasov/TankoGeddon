// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannon.h"
#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ACannon::ACannon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;


	CannonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CannonMesh"));
	RootComponent = CannonMesh;

	ProjecttileSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("ProjecttileSpawnPoint"));
	ProjecttileSpawnPoint->SetupAttachment(CannonMesh);
}

void ACannon::Fire()
{
	//cannon fire test
	if (!bCanFire || WhizBang == 0)
	{
		GEngine->AddOnScreenDebugMessage(10, 1, FColor::Red, "Not bullet");
		return;
	}
	
	bCanFire = false;
	

	if (CannonType == ECannonType::FireProjectile)
	{
		WhizBang--;
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Fire projectile ")));
	}
	else
	{
		WhizBang--;
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Purple, FString::Printf(TEXT("Fire trace ")));
	}
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Bullet = %d"), WhizBang));
	GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &ACannon::Reload, ReloadTime, false);
}

void ACannon::FireSpecial()
{
	
	if (ActualBang == BangSize)
	{
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
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, FString::Printf(TEXT("Fire projectile")));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, FString::Printf(TEXT("Fire trace")));
	}
	GetWorld()->GetTimerManager().SetTimer(BangTimer, this, &ACannon::Bang, BangInterval, false);

	Bang();
}

void ACannon::Reload()
{
	bCanFire = true;
}
void ACannon::Bang()
{
	if (!bCanFire || WhizBang == 0)
	{
		GEngine->AddOnScreenDebugMessage(10, 1, FColor::Red, "Not bullet");
		return;
	}

	bCanFire = false;
}


