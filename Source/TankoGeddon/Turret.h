// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DamageTaker.h"
#include "GameStruct.h"
#include "MachinePawn.h"
#include "Particles/ParticleSystemComponent.h"
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

	 FVector GetEyesPosition();

	 void Destroyed();		//Метод уничтожения пушки
	 void Targeting();		//Метод слежения за противником
	 void RotateToPlayer();	//Метод Вращение за игроком 
	
	 bool CanFire();			//Можем ли мы стрелять

	 

	 //Только добавил
	 bool IsPlayerSeen();		//Видимость игрока турелью
	 bool IsPlayerInRange();	//Метод проверка нахождения игрока в зоне видимости


	

	 UPROPERTY()
	 class APawn* PlayerPawn;
	 //Компонент отвечающий за стрельбу
	 UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting")
	 float TargetingRange = 1000.0f;

	 //скорость поворота
	 UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting")
		 float TargetingSpeed = 0.1f;
	 //Угол видения игрока
	 UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting")
		 float TargetingRate = 0.005f;
	 //Точность 
	 UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting")
		 float Accurency = 30.0f;

	

	 //Путь до нашей мешки
	 const FString BodyMeshPath = "StaticMesh'/Game/CSC/Meshes/SM_CSC_Tower1.SM_CSC_Tower1'";

	 const FString TurretMeshPath = "StaticMesh'/Game/CSC/Meshes/SM_CSC_Gun1.SM_CSC_Gun1'";

};
