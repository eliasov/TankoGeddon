// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class TANKOGEDDON_API ATankAIController : public AAIController
{
	GENERATED_BODY()

protected:
	//Указатель танка
	UPROPERTY()
	class ATankPawn* TankPawn;

	UPROPERTY()
		class APawn* PlayerPawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI | Movement", Meta = (MakeEditWidget = true)) 
	TArray<FVector> PatrollingPath; //Путь

	int32 CurrentPatrollingIndex = 0; //Индекс патрулирования Нулевая точка

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI | Movement")
	float MovementAccurency; //Видимость

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI | Targeting")
		float TargetingRange = 1000.0f; //Дистанция слежения

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI | Targeting")
		float TargetingSpeed = 0.1f; //Скорость 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI | Targeting")
		float Accurency = 10.0f; //Точность

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	float GetRotationValue(); //Вращение
	void Targeting();
	void RotateToPlayer();
	bool IsPlayerRange();//Находится ли он в радиусе
	bool CanFire();//Может ли стрелять

	void Fire();
	bool IsPlayerSeen();//Видим ли мы игрока

	//метод на инициализацию(Проверка на возрождения танка и задаем ему путь)
	void Initialize();

};
