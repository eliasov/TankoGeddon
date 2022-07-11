// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"
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

void ATurret::Destroyed()		//����� ����������� �����
{
	if (Cannon)
		Cannon->Destroy();
}

void ATurret::Targeting()		//����� �������� �� �����������
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

void ATurret::RotateToPlayer()	//����� �������� �� ������� 
{
	//�������� ������� ����� ������� � �����
	FRotator targetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), PlayerPawn->GetActorLocation());
	//�������� �������� ������
	FRotator TurretRotation = TurretMesh->GetComponentRotation();
	//�.�. �� ���������� ����� ����, ��� ������ ������������
	targetRotation.Pitch = TurretRotation.Pitch;
	targetRotation.Roll = TurretRotation.Roll;
	//������ ����� ������ �������� (��� ��� ����� ������)
	TurretMesh->SetWorldRotation(FMath::Lerp(TurretRotation, targetRotation, TargetingSpeed));


}

bool ATurret::IsPlayerInRange()	//����� �������� ���������� ������ � ���� ���������
{
	//���� ��������� ������
	return FVector::Distance(PlayerPawn->GetActorLocation(), GetActorLocation()) <= TargetingRange;
}

bool ATurret::CanFire()			//����� �� �� ��������
{
	FVector targetingDir = TurretMesh->GetForwardVector();
	FVector dirToPlayer = PlayerPawn->GetActorLocation() - GetActorLocation();
	dirToPlayer.Normalize();

	float aimAngle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(targetingDir, dirToPlayer)));
	return aimAngle <= Accurency;
}




