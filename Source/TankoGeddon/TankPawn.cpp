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

// Sets default values
ATankPawn::ATankPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	RootComponent = BodyMesh;

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	TurretMesh->SetupAttachment(BodyMesh);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(BodyMesh);
	SpringArm->bDoCollisionTest = false;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bInheritRoll = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	CannonSetupPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("CannonSetupPoint"));
	CannonSetupPoint->SetupAttachment(TurretMesh);
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



void ATankPawn::Fire()
{
	if (Cannon)
	{
		Cannon->Fire();
	}
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

	//Tank turret rotation
	FVector MousePos = TankController->GetMousePosition();
	//Defining rotation
	FRotator targetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), MousePos);
	//Getting the rotation of our turret
	FRotator TurretRotation = TurretMesh->GetComponentRotation();


	//Equate unnecessary coordinates y
	targetRotation.Pitch = TurretRotation.Pitch;
	//Equate unnecessary coordinates x
	targetRotation.Roll = TurretRotation.Roll;


	//Set the rotation
	TurretMesh->SetWorldRotation(FMath::Lerp(TurretRotation, targetRotation, RotateInterpolationKey));

}

void ATankPawn::BeginPlay()
{
	Super::BeginPlay();
	//Tank spawn coordinates
	SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, 0.0f));
	//Implementing getting the player controller
	TankController = Cast<ATankController>(GetController());

	SetupCannon(CannonClass);
}

void ATankPawn::SetupCannon(TSubclassOf<ACannon> newCannonClass)
{
	if (!newCannonClass)
	{
		
		return;
	}
	if (Cannon)
	{
		Cannon->Destroy();
	}
	FActorSpawnParameters params;
	params.Instigator = this;
	params.Owner = this;

	Cannon = GetWorld()->SpawnActor<ACannon>(newCannonClass, params);

	Cannon->AttachToComponent(CannonSetupPoint, FAttachmentTransformRules::SnapToTargetIncludingScale);

	
}


void ATankPawn::WeaponChange()
{
	if (bWeaponChange)
	{
		SetupCannon(SecondCannonClass);
		bWeaponChange = false;
	}
	else
	{
		SetupCannon(EquippedCannonClass);
		bWeaponChange = true;
	}
}
void ATankPawn::SetAmount(int bullets)
{
	Cannon->WhizBang = Cannon->WhizBang + bullets;
}

