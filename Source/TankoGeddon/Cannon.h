// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameStruct.h"
#include "ProjectilePool.h"
#include "Projectile.h"
#include "Cannon.generated.h"



class AProjectilePool;
class UCameraShake;

UCLASS()
class TANKOGEDDON_API ACannon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACannon();

	void Fire();
	void FireSpecial();
	//shooting type
	void Reload();

	bool IsReadyToFire() { return bCanFire; };

	void CreateProjectilePool();
	void Deactivate();
	
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
		int32 WhizBang = 20;

protected:
	virtual void BeginPlay() override;
	//Cannon property
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UStaticMeshComponent* CannonMesh;

	//Method projectile spawn 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UArrowComponent* ProjectileSpawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	ECannonType CannonType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	float ReloadTime = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	float BangTime = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		bool fireTextTurrent = true;

	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	float BangSize = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	float BangInterval = 0.2f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
		float FireRange = 100.0f;


	//pointer to projetile class
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		TSubclassOf<AProjectilePool> ProjectilePoolClass;

	

	UPROPERTY()
		AProjectilePool* ProjectilePool;

	//Effect
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		class UParticleSystemComponent* ShootEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		class UAudioComponent* AudioEffect;

	//Effects ������� ������ ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shaking")
	class UForceFeedbackEffect* ShakingEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shaking")
	TSubclassOf<class UCameraShakeBase> ShootShaking;


	



	FTimerHandle ReloadTimer;
	FTimerHandle BangTimer;
	FTimerHandle DeactivateTimer;
	FTimerHandle MoveTimer;
	int32 ActualBang = 0;

private:
	//Ammo accounting check
	bool bCanFire = true;
	void Bang();
	bool bIsActivation = false;
	
	
};
