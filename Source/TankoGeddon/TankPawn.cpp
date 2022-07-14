// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPawn.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "TankController.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/SceneComponent.h"
#include "Cannon.h"
#include "Components\ArrowComponent.h"
#include "HealthComponent.h"

// Sets default values
ATankPawn::ATankPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(BodyMesh);
	SpringArm->bDoCollisionTest = false;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bInheritRoll = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

}

void ATankPawn::MoveForward(float Value)
{
	TargetForwardAxisValue = Value;
}
void ATankPawn::MoveRight(float Value)
{
	TargetRightAxisValue = Value;
}

void ATankPawn::RotateRight(float Value)
{
	RotateRightAxisValue = Value;
}


void ATankPawn::FireSpecial()
{
	if (Cannon)
	{
		Cannon->FireSpecial();
	}
}

void ATankPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//Move Tank
	FVector CurrentLocation = GetActorLocation();
	FVector forwardVector = GetActorForwardVector();
	FVector rightVector = GetActorRightVector();
	FVector movePosition1 = CurrentLocation + forwardVector * MoveSpeed * TargetForwardAxisValue;
	FVector movePosition2 = rightVector * MoveSpeed * TargetRightAxisValue;
	FVector movePosition = movePosition1 + movePosition2;
	SetActorLocation(movePosition, true);


	//Rotate Tank
	CurrentRotateAxisValue = FMath::Lerp(CurrentRotateAxisValue, RotateRightAxisValue, InterpolationKey);
	float YawRotation = RotationSpeed * RotateRightAxisValue * DeltaSeconds;

	//UE_LOG(LogTemp, Warning, TEXT("CurrentRotateAxis Value: %f, RotateRightAxisValue: %f"), CurrentRotateAxisValue, RotateRightAxisValue);

	FRotator CurrentRotation = GetActorRotation();

	YawRotation = CurrentRotation.Yaw + YawRotation;

	FRotator newRotation = FRotator(0.0f, YawRotation, 0.0f);
	SetActorRotation(newRotation);

	if (TankController)
	{
		//Tank turret rotation
		FVector MousePos = TankController->GetMousePosition();
		
		RotateTurretTo(MousePos);
	}
}

void ATankPawn::BeginPlay()
{
	Super::BeginPlay();
	//Tank spawn coordinates
	SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, 0.0f));
	//Implementing getting the player controller
	TankController = Cast<ATankController>(GetController());

}

void ATankPawn::WeaponChange()
{
	
	TSubclassOf<ACannon> reverseCannon = EquippedCannonClass;
	EquippedCannonClass = SecondCannonClass;
	SecondCannonClass = reverseCannon;
	SetupCannon(EquippedCannonClass);
}
void ATankPawn::SetAmount(int bullets)
{
	Cannon->WhizBang = Cannon->WhizBang + bullets;
}

FVector ATankPawn::GetTurretForwardVector() //Вращения турели аи
{
	return TurretMesh->GetForwardVector();
}

void ATankPawn::RotateTurretTo(FVector TargetPosition)
{
	FRotator targetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetPosition);
	//Getting the rotation of our turret
	FRotator TurretRotation = TurretMesh->GetComponentRotation();


	//Equate unnecessary coordinates y
	targetRotation.Pitch = TurretRotation.Pitch;
	//Equate unnecessary coordinates x
	targetRotation.Roll = TurretRotation.Roll;


	//Set the rotation
	TurretMesh->SetWorldRotation(FMath::Lerp(TurretRotation, targetRotation, RotateInterpolationKey));
}

FVector ATankPawn::GetEyesPosition()
{
	return CannonSetupPoint->GetComponentLocation();//возвращаем позицию глаз АИ танка
}

