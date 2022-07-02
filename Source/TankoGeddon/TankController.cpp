// Fill out your copyright notice in the Description page of Project Settings.


#include "TankController.h"
#include "TankPawn.h"

//Cursor display properties
ATankController::ATankController()
{
	bShowMouseCursor = true;
}

void ATankController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &ATankController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ATankController::MoveRight);
	InputComponent->BindAxis("RotateRight", this, &ATankController::RotateRight);
	InputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &ATankController::Fire);
	InputComponent->BindAction("FireSpecial", EInputEvent::IE_Pressed, this, &ATankController::FireSpecial);
}

void ATankController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//Variable to save
	FVector mouseDirection;
	//Method mouse position transfer
	DeprojectMousePositionToWorld(MousePos, mouseDirection);
	//Define a vector between the player and the mouse position
	FVector TankPosition = TankPawn->GetActorLocation();
	//Equate the coordinates along the axis Z
	MousePos.Z = TankPosition.Z;

	//The direction vector is equal to the difference between the mouse position and the player position
	FVector dir = MousePos - TankPosition;
	//Normalize the vector from -1 to 1
	dir.Normalize();
	
	MousePos = TankPosition + dir * 1000.0f;
	//Vector rendering
	DrawDebugLine(GetWorld(), TankPosition, MousePos, FColor::Green, false, 0.5f, 0, 5);




}

void ATankController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	TankPawn = Cast<ATankPawn>(InPawn);
}

void ATankController::MoveForward(float Value)
{
	if(TankPawn)
		TankPawn->MoveForward(Value);
	
}
void ATankController::MoveRight(float Value)
{
	if(TankPawn)
	TankPawn->MoveRight(Value);
}

void ATankController::RotateRight(float Value)
{
	if (TankPawn)
		TankPawn->RotateRight(Value);
}

void ATankController::Fire()
{
	if (TankPawn)
	{
		TankPawn->Fire();
	}
}

void ATankController::FireSpecial()
{
	if (TankPawn)
	{
		TankPawn->FireSpecial();
	}
}

