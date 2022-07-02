// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TankPawn.generated.h"

class UStaticMeshComponent;
class ACannon;

UCLASS()
class TANKOGEDDON_API ATankPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATankPawn();

	
	void MoveForward(float Value);
	void MoveRight(float Value);
	void RotateRight(float Value);

	void Fire();
	void FireSpecial();

	virtual void Tick(float DeltaSeconds) override;

	virtual void BeginPlay() override;

	void SetupCannon();

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* BodyMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret | Components")
	TSubclassOf<ACannon> CannonClass;

	UPROPERTY()
	ACannon* Cannon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
		float MoveSpeed = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
		float RotationSpeed = 10.0f;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Movement")
		float TargetForwardAxisValue = 0.0f;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Movement")
		float TargetRightAxisValue = 0.0f;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
		float InterpolationKey= 0.1f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
		float RotateInterpolationKey = 0.1f;
	
	//Getting a pointer to a controller
	UPROPERTY()
	class ATankController* TankController;

	

private:


	float RotateRightAxisValue = 0.0f;
	float CurrentRotateAxisValue = 0.0f;


};
