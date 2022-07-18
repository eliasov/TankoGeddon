// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "TankPawn.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Pawn.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	Initialize();

}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);//постоянное движение вперед

	if (!TankPawn)
	{
		Initialize();
	}
	if (!TankPawn)
	{
		return;
	}

	TankPawn->MoveForward(1);//Движение к нашей точки

	float RotationValue = GetRotationValue();

	TankPawn->RotateRight(RotationValue);

	Targeting();
}

float ATankAIController::GetRotationValue()
{
	FVector currentPoint = PatrollingPath[CurrentPatrollingIndex];//Движение к определенной точки(Точка зависит от нашего индекса)
	FVector pawnLocation = TankPawn->GetActorLocation();//Получаем конкретную точку и позицию нашего игрока
	if (FVector::Distance(currentPoint, pawnLocation) <= MovementAccurency)//Проверяем дистанцию
	{
		CurrentPatrollingIndex++;//(Если дистанция между точкой и нашего игрока меньше двигаемся от точки к точке)
		if (CurrentPatrollingIndex >= PatrollingPath.Num())//Проверка выход за границы
		{
			CurrentPatrollingIndex = 0;
		}
	}

	//Поворот нашего танка
	FVector moveDirection = currentPoint - pawnLocation;
	//Нормализуем вектор и высчитываем расстояние между точками
	moveDirection.Normalize();

	FVector forwardDirection = TankPawn->GetActorForwardVector(); //Вектор вперед
	FVector rightDirection = TankPawn->GetActorRightVector(); //Вектор вправо

	DrawDebugLine(GetWorld(), pawnLocation, currentPoint, FColor::Green, false, 0.1f, 0, 5);//Отрисовка линии между аи танком и нашем танком


	float ForwardAngle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(forwardDirection, moveDirection)));//Скалярное произведение между вектором направления и moveDirection
	float RightdAngle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(rightDirection, moveDirection)));

	//Проверяем вращение танка
	float RotationValue = 0;
	if (ForwardAngle > 5)
	{
		RotationValue = 1;
	}
	if (RightdAngle > 90)
	{
		RotationValue = -RotationValue;
	}
	return RotationValue;//Возвращаем наше вращение
}

void ATankAIController::Targeting()
{
	if (CanFire())
		Fire();
	else
		RotateToPlayer();
}

void ATankAIController::RotateToPlayer() //Получаем позицию и возвращаемся к нашему игроку
{
	if (IsPlayerRange())
		TankPawn->RotateTurretTo(PlayerPawn->GetActorLocation());
}

bool ATankAIController::IsPlayerRange()//Проверяем дистанцию
{
	return FVector::Distance(TankPawn->GetActorLocation(), PlayerPawn->GetActorLocation()) <= TargetingRange;

}

bool ATankAIController::CanFire()
{
	if (!IsPlayerSeen())
	{
		return false;
	}
	FVector targetDir = TankPawn->GetTurretForwardVector();//получаем позицию нашей терели
	FVector dirToPlayer = PlayerPawn->GetActorLocation() - TankPawn->GetActorLocation();
	dirToPlayer.Normalize();
	float aimAngele = FMath::RadiansToDegrees(acosf(FVector::DotProduct(targetDir, dirToPlayer)));

	return aimAngele <= Accurency;
}

void ATankAIController::Fire()
{
	TankPawn->Fire();
}

bool ATankAIController::IsPlayerSeen()
{
	if (PlayerPawn) 
	{
		FVector playerPos = PlayerPawn->GetActorLocation();	//Присваиваем позицию игрока
		FVector eyesPos = TankPawn->GetEyesPosition();		//Присваиваем позицию глаз

		FHitResult hitResult;

		FCollisionQueryParams traceParams =
			FCollisionQueryParams(FName(TEXT("FireTrace")), true, this);
		traceParams.bTraceComplex = true;
		traceParams.AddIgnoredActor(TankPawn);				//Игнорируем танк павн
		traceParams.bReturnPhysicalMaterial = false;		//Не возвращаем физ материал

		if (GetWorld()->LineTraceSingleByChannel(hitResult, eyesPos, playerPos, ECollisionChannel::ECC_Visibility, traceParams))
		{
			if (hitResult.GetActor())
			{
				DrawDebugLine(GetWorld(), eyesPos, hitResult.Location, FColor::Cyan, false, 0.5f, 0, 10);
				return hitResult.GetActor() == PlayerPawn;	//Возвращаем результат нашему игроку

			}
		}
		DrawDebugLine(GetWorld(), eyesPos, playerPos, FColor::Cyan, false, 0.5f, 0, 10); //Рисуем линию не до игрока
		
	}
	return false;
}

void ATankAIController::Initialize()
{
	TankPawn = Cast<ATankPawn>(GetPawn()); //Получаем указатель на нашего игрока
	
	if (!TankPawn)
	{
		return;
	}
	PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	FVector pawnLocation = TankPawn->GetActorLocation();//Отслеживаем точки танка
	MovementAccurency = TankPawn->GetAccurency(); //Получаем точность
	TArray<FVector> points = TankPawn->GetPatrollingPoints();//получаем точки 

	// следуем по точкам перемещая индекс
	for (FVector point : points)
	{
		PatrollingPath.Add(point);//Преобразование массива точек для работы в контроллере
	}
	CurrentPatrollingIndex = 0; //Начинаем с нулевого индекса
}
