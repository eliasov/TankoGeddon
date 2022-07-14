// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "DamageTaker.h"
#include "GameStruct.h"
#include "Components/AudioComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "MachinePawn.generated.h"

class UStaticMeshComponent;
class ACannon;

UCLASS()
class TANKOGEDDON_API AMachinePawn : public APawn, public IDamageTaker
{
	GENERATED_BODY()

public:
	AMachinePawn();

	virtual void TakeDamage(FDamageData DamageData) override;//����� ��������� �� ��������� �����
	void Fire(); //����� ����� ��������
	void SetupCannon(TSubclassOf<ACannon> newCannonClass); //����� ����� ��������� �����.
	


protected:
	
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* BodyMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class UBoxComponent* BoxComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class UArrowComponent* CannonSetupPoint; //����� �������� �����

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret | Components")
		TSubclassOf<ACannon> EquippedCannonClass;//����� �����

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		class UHealthComponent* HealthComponent; //��������
	
	//Effect

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		class UAudioComponent* AudioEffectDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		class UAudioComponent* AudioEffectDie;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		class UParticleSystemComponent* ShootEffectDie;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		class UParticleSystemComponent* ShootEffectDamage;

	



	UPROPERTY()
		ACannon* Cannon;


	UFUNCTION()
		void Die();//����� �� ������

	UFUNCTION()
		void DamageTaked(float DamageValue);//����� �� ��������� �����


};
