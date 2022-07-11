// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DamageTaker.h"
#include "GameStruct.h"
#include "MachinePawn.h"
#include "Turret.generated.h"


class UStaticMeshComponent;
class ACannon;
UCLASS()
class TANKOGEDDON_API ATurret : public AMachinePawn
{
	GENERATED_BODY()

 public:
	ATurret();

 protected:
	 // Called when the game starts or when spawned
	 virtual void BeginPlay() override;

	 void Destroyed();		//����� ����������� �����
	 void Targeting();		//����� �������� �� �����������
	 void RotateToPlayer();	//����� �������� �� ������� 
	 bool IsPlayerInRange();	//����� �������� ���������� ������ � ���� ���������
	 bool CanFire();			//����� �� �� ��������

	 UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	 TSubclassOf<ACannon> CannonClass;

	 UPROPERTY()
	 class APawn* PlayerPawn;
	 //��������� ���������� �� ��������
	 UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting")
	 float TargetingRange = 1000.0f;

	 //�������� ��������
	 UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting")
		 float TargetingSpeed = 0.1f;
	 //���� ������� ������
	 UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting")
		 float TargetingRate = 0.005f;
	 //�������� 
	 UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting")
		 float Accurency = 30.0f;

	 //���� �� ����� �����
	 const FString BodyMeshPath = "StaticMesh'/Game/CSC/Meshes/SM_CSC_Tower1.SM_CSC_Tower1'";

	 const FString TurretMeshPath = "StaticMesh'/Game/CSC/Meshes/SM_CSC_Gun1.SM_CSC_Gun1'";

};
