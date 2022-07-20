// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "PhysicProjectile.generated.h"

/**
 * 
 */
UCLASS()
class TANKOGEDDON_API APhysicProjectile : public AProjectile
{
	GENERATED_BODY()

public:

	APhysicProjectile();

	virtual void  Start() override;

protected:

	virtual void Move() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UPhysicsComponent* PhysicsComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UParticleSystemComponent* TrailEffect;

	
	//паметры за настройку движения
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement params")
	float MovementAccurency = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement params")
		float MaxTimeSimulation = 50.0f; //Время обновления

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement params")
	float TimeStep = 1.0f;//Шаг обновления

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement params")
	float MoveSpeedPhysics = 50.0f;//Скорость 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement params")
	bool bShowTrajectory = true;//Отрисовка траектории

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement params")
		float ExplodeRadius = 50.0f;


	//Параметры вектора движения, траектория и точка траектории
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement params")
	FVector MoveVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement params")
	TArray<FVector> CurrentTrajectory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement params")
	int32 TrajectoryPointIndex;

	void Explode();


};
