// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DamageTaker.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/AudioComponent.h"
#include "TaknFactory.generated.h"

UCLASS()
class TANKOGEDDON_API ATaknFactory : public AActor, public IDamageTaker
{
	GENERATED_BODY()
	
public:	
	
	ATaknFactory();

protected:

	virtual void BeginPlay() override;

	UFUNCTION()//Метод на появления танка
		void SpawnTank();

	UFUNCTION()//Метод получение урона
	virtual void TakeDamage(FDamageData DamageData) override; 

	UFUNCTION()//Метод на смерть танка
	void Die();

	UFUNCTION()//Метод получение урона
	void DamageTaked(float DamageValue);

	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UStaticMeshComponent* BuildingMesh; //Представление 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		class UStaticMeshComponent* BuildingMesh2; //Представление 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UBoxComponent* BoxCollider; //Бокс коллайдер

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		class UBoxComponent* BoxCollider2; //Бокс коллайдер

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UHealthComponent* HealthComponent;//Компонент здоровья

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UArrowComponent* TankSpawnPoint; //Точка возрождения танка

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn parameters")
	TSubclassOf<class ATankPawn> SpawnTankClass; //Танки которые мы будем спавнить

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn parameters")
	float SpawnTankRate = 2.0f; //Скорость возрождения

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn parameters")
		TArray<class ATargetPoint*> TankWayPoints; //Путь

	//фабрика работает, переход на другой уровень недоступен,после её уничтожения — открывается
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MapLoader")
	class AMapLoader* MapLoader;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UAudioComponent* AudioEffectRespawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UAudioComponent* AudioEffectDieFactory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UParticleSystemComponent* EffectRespawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UParticleSystemComponent* FactoryEffectDie;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		class UParticleSystemComponent* FactoryEffectDamage;

};
