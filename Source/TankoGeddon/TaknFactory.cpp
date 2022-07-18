// Fill out your copyright notice in the Description page of Project Settings.


#include "TaknFactory.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "HealthComponent.h"
#include "TankPawn.h"
#include "Kismet/GameplayStatics.h"
#include "MapLoader.h"
#include "Components/AudioComponent.h"
#include "Particles/ParticleSystemComponent.h"


ATaknFactory::ATaknFactory()
{
 	
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = SceneComponent;

	BuildingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BuildingMesh"));
	BuildingMesh->SetupAttachment(SceneComponent);
	BuildingMesh->SetHiddenInGame(false);

	BuildingMesh2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BuildingMesh2"));
	BuildingMesh2->SetupAttachment(SceneComponent);
	BuildingMesh2->SetHiddenInGame(true);

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	BoxCollider->SetupAttachment(BuildingMesh);

	BoxCollider2 = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider2"));
	

	TankSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("TankSpawnPoint"));
	TankSpawnPoint->SetupAttachment(BuildingMesh);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	HealthComponent->OnHealthChanged.AddUObject(this, &ATaknFactory::DamageTaked);
	HealthComponent->OnDie.AddUObject(this, &ATaknFactory::Die);

	AudioEffectRespawn = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioEffectRespawn"));
	AudioEffectDieFactory = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioEffectDieFactory"));

	EffectRespawn = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EffectRespawn"));
	EffectRespawn->SetupAttachment(BuildingMesh);

	FactoryEffectDie = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FactoryEffectDie"));
	FactoryEffectDie->SetupAttachment(BuildingMesh);

	FactoryEffectDamage = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FactoryEffectDamage"));
	FactoryEffectDamage->SetupAttachment(BuildingMesh);

	
}

void ATaknFactory::BeginPlay()
{
	Super::BeginPlay();
	if (MapLoader)
	{
		MapLoader->SetIsActivated(false);
	}
	FTimerHandle SpawnTimer;
	//Таймер вызывающий спавн танка
	GetWorld()->GetTimerManager().SetTimer(SpawnTimer, this, &ATaknFactory::SpawnTank, SpawnTankRate, true);
}

void ATaknFactory::SpawnTank()
{
	// передаем ему вращение, позицию и размер вектора
	FTransform spawnTransform(TankSpawnPoint->GetComponentRotation(), TankSpawnPoint->GetComponentLocation(), FVector(1));
	//Создаем через конструктор спавн танка,
	EffectRespawn->ActivateSystem(false);
	ATankPawn* newTank = GetWorld()->SpawnActorDeferred<ATankPawn>(SpawnTankClass, spawnTransform, this, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	AudioEffectRespawn->Play();
	newTank->SetPatrollingPoints(TankWayPoints);

	//Вызываем финиш спавн
	UGameplayStatics::FinishSpawningActor(newTank, spawnTransform);
}

void ATaknFactory::TakeDamage(FDamageData DamageData)
{
	HealthComponent->TakeDamage(DamageData);
}

void ATaknFactory::Die()
{
	if (MapLoader)
	{
		MapLoader->SetIsActivated(true);
	}
	AudioEffectDieFactory->Play();
	FactoryEffectDie->ActivateSystem(false);

	BuildingMesh->SetHiddenInGame(true);
	BuildingMesh2->SetHiddenInGame(false);
}

void ATaknFactory::DamageTaked(float DamageValue)
{
	UE_LOG(LogTemp, Warning, TEXT("Factory %s take Damage: %f, Health: %f"), *GetName(), DamageValue, HealthComponent->GetHealth());
	FactoryEffectDamage->ActivateSystem(false);
}

