// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"
#include "TankPawn.h"
#include "Components\StaticMeshComponent.h"
#include "Components\ArrowComponent.h"
#include "Components\BoxComponent.h"
#include "Cannon.h"
#include "Kismet\KismetMathLibrary.h"
#include "UObject\UObjectGlobals.h"
#include "Engine\StaticMesh.h"
#include "HealthComponent.h"

// Sets default values
ATurret::ATurret()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;


	UStaticMesh* BodyMeshTemp = LoadObject<UStaticMesh>(this, *BodyMeshPath);
	if (BodyMeshTemp)
		BodyMesh->SetStaticMesh(BodyMeshTemp);

	UStaticMesh* TurretMeshTemp = LoadObject<UStaticMesh>(this, *TurretMeshPath);
	if (TurretMeshTemp)
		TurretMesh->SetStaticMesh(TurretMeshTemp);

	
}


void ATurret::BeginPlay()
{
	Super::BeginPlay();

	PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	FTimerHandle TargetingTimer;
	GetWorld()->GetTimerManager().SetTimer(TargetingTimer, this, &ATurret::Targeting,TargetingRate, true, TargetingRate);


}

FVector ATurret::GetEyesPosition()
{
	return CannonSetupPoint->GetComponentLocation();
}

void ATurret::Destroyed()		//ћетод уничтожени€ пушки
{
	if (Cannon) 
	{
		Cannon->Destroy();
		
	}
}


void ATurret::Targeting()		//ћетод слежение за противником
{
	if (IsPlayerInRange())
	{
		RotateToPlayer();
		if (CanFire() && Cannon && Cannon->IsReadyToFire())
		{
			Fire();
		}
	}

	
}

void ATurret::RotateToPlayer()	//ћетод вращение за игроком 
{
	//ѕолучаем поворот между началом и целью
	FRotator targetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), PlayerPawn->GetActorLocation());
	//получаем вращение турели
	FRotator TurretRotation = TurretMesh->GetComponentRotation();
	//т.к. мы пользуемс€ одной осью, две другие приравниваем
	targetRotation.Pitch = TurretRotation.Pitch;
	targetRotation.Roll = TurretRotation.Roll;
	//задаем нашей турели вращении (что она видит огрока)
	TurretMesh->SetWorldRotation(FMath::Lerp(TurretRotation, targetRotation, TargetingSpeed));


}

bool ATurret::IsPlayerInRange()	//ћетод проверка нахождени€ игрока в зоне видимости
{
	//«она видимости игрока
	return FVector::Distance(PlayerPawn->GetActorLocation(), GetActorLocation()) <= TargetingRange;
}


bool ATurret::CanFire()			//ћожем ли мы стрел€ть
{
	if (!IsPlayerSeen())
	{
		return false;
	}
	FVector targetingDir = TurretMesh->GetForwardVector();
	FVector dirToPlayer = PlayerPawn->GetActorLocation() - GetActorLocation();
	dirToPlayer.Normalize();

	float aimAngle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(targetingDir, dirToPlayer)));
	return aimAngle <= Accurency;
}


bool ATurret::IsPlayerSeen()
{
	FVector playerPos = PlayerPawn->GetActorLocation();	//ѕрисваиваем позицию игрока
	FVector eyesPos = GetEyesPosition();		//ѕрисваиваем позицию глаз

	FHitResult hitResult;

	FCollisionQueryParams traceParams =
		FCollisionQueryParams(FName(TEXT("FireTrace")), true, this);
	traceParams.bTraceComplex = true;
	//traceParams.AddIgnoredActor(TankPawn);				//»гнорируем танк павн
	traceParams.bReturnPhysicalMaterial = false;		//Ќе возвращаем физ материал

	if (GetWorld()->LineTraceSingleByChannel(hitResult, eyesPos, playerPos, ECollisionChannel::ECC_Visibility, traceParams))
	{
		if (hitResult.GetActor())
		{
			DrawDebugLine(GetWorld(), eyesPos, hitResult.Location, FColor::Cyan, false, 0.5f, 0, 10);
			return hitResult.GetActor() == PlayerPawn;	//¬озвращаем результат нашему игроку

		}
	}
	DrawDebugLine(GetWorld(), eyesPos, playerPos, FColor::Cyan, false, 0.5f, 0, 10); //–исуем линию не до игрока
	return false;
}




