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

	UFUNCTION()//����� �� ��������� �����
		void SpawnTank();

	UFUNCTION()//����� ��������� �����
	virtual void TakeDamage(FDamageData DamageData) override; 

	UFUNCTION()//����� �� ������ �����
	void Die();

	UFUNCTION()//����� ��������� �����
	void DamageTaked(float DamageValue);

	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UStaticMeshComponent* BuildingMesh; //������������� 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		class UStaticMeshComponent* BuildingMesh2; //������������� 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UBoxComponent* BoxCollider; //���� ���������

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		class UBoxComponent* BoxCollider2; //���� ���������

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UHealthComponent* HealthComponent;//��������� ��������

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UArrowComponent* TankSpawnPoint; //����� ����������� �����

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn parameters")
	TSubclassOf<class ATankPawn> SpawnTankClass; //����� ������� �� ����� ��������

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn parameters")
	float SpawnTankRate = 2.0f; //�������� �����������

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn parameters")
		TArray<class ATargetPoint*> TankWayPoints; //����

	//������� ��������, ������� �� ������ ������� ����������,����� � ����������� � �����������
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
