// Fill out your copyright notice in the Description page of Project Settings.


#include "PhysicProjectile.h"
#include "PhysicsComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "CollisionQueryParams.h"
#include "DrawDebugHelpers.h"
#include "DamageTaker.h"
#include "GameStruct.h"

APhysicProjectile::APhysicProjectile()
{
	PhysicsComponent = CreateDefaultSubobject<UPhysicsComponent>(TEXT("PhysicsComponent"));
	

	TrailEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("TrailEffect"));
	TrailEffect->SetupAttachment(RootComponent);
}

void APhysicProjectile::Start()
{
	//переопредел€ем нашу логику

	MoveVector = GetActorForwardVector() * MoveSpeedPhysics;//ѕолучаем вектор движени€
	CurrentTrajectory = PhysicsComponent->GenerateTrajectory(GetActorLocation(), MoveVector, MaxTimeSimulation, TimeStep, 0.0f); //ѕолучаем траекторию движени€ 
	//ќтрисовываем траекторию
	if (bShowTrajectory)
	{
		for (FVector position : CurrentTrajectory)
		{
			DrawDebugSphere(GetWorld(), position, 5, 8, FColor::Purple, true, 1, 0, 2);
		}
		
	}
	TrajectoryPointIndex = 0;
	TrailEffect->ActivateSystem();
	Super::Start();
}

void APhysicProjectile::Move()
{
	FVector CurrentMoveVector = CurrentTrajectory[TrajectoryPointIndex] - GetActorLocation();
	UE_LOG(LogTemp, Warning, TEXT("Not normalize: %s"), *CurrentMoveVector.ToString());
	CurrentMoveVector.Normalize();
	UE_LOG(LogTemp, Warning, TEXT("Normalize: %s"), *CurrentMoveVector.ToString());
	FVector newLocation = GetActorLocation() + CurrentMoveVector * MoveSpeed * MoveRate;
	SetActorLocation(newLocation);

	if (FVector::Distance(newLocation, CurrentTrajectory[TrajectoryPointIndex]) <= MovementAccurency)
	{
		TrajectoryPointIndex++;
		if (TrajectoryPointIndex >= CurrentTrajectory.Num())
		{
			if (bEnabelExplode)
			{
				ExplodeProject();
			}
			Destroy();
		}
		else
		{
			FRotator newRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(),
			CurrentTrajectory[TrajectoryPointIndex]);
			SetActorRotation(newRotation);
		}
	}

}

