// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameStruct.h"
#include "Cannon.generated.h"

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
	void Bang();

protected:
	//Cannon property
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	class UStaticMeshComponent* CannonMesh;

	//Method projectile spawn 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	class UArrowComponent* ProjecttileSpawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	ECannonType CannonType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	float ReloadTime = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	int32 WhizBang = 20;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	float BangSize = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	float BangInterval = 0.1f;



	FTimerHandle ReloadTimer;
	FTimerHandle BangTimer;
	int32 ActualBang = 0;

private:
	//Ammo accounting check
	bool bCanFire = true;

	
	
};
