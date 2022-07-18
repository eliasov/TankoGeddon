// Fill out your copyright notice in the Description page of Project Settings.


#include "MachinePawn.h"
#include "Components\StaticMeshComponent.h"
#include "Components\ArrowComponent.h"
#include "Components\BoxComponent.h"
#include "HealthComponent.h"
#include "Cannon.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AMachinePawn::AMachinePawn()
{
	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	RootComponent = BodyMesh;

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	TurretMesh->SetupAttachment(BodyMesh);

	CannonSetupPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("CannonSetupPoint"));
	CannonSetupPoint->SetupAttachment(TurretMesh);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	BoxComponent->SetupAttachment(BodyMesh);

	//Создаем HealthComponent
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	//подписываемся на наши методы(Какой метод мы хотим вызвать при смерти)
	HealthComponent->OnDie.AddUObject(this, &AMachinePawn::Die);
	//подписываемся на наши методы(Какой метод мы хотим вызвать при нанесении урона)
	HealthComponent->OnHealthChanged.AddUObject(this, &AMachinePawn::DamageTaked);

	//Audio effect
	AudioEffectDamage = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioEffectDamage"));
	AudioEffectDie = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioEffectDie"));

	ShootEffectDamage = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ShootEffectDamage"));
	ShootEffectDamage->SetupAttachment(BodyMesh);

	ShootEffectDie = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ShootEffectDie"));
	ShootEffectDie->SetupAttachment(BodyMesh);
}



void AMachinePawn::TakeDamage(FDamageData DamageData)
{
	HealthComponent->TakeDamage(DamageData);
	AudioEffectDamage->Play();
	ShootEffectDamage->ActivateSystem(false);
}

void AMachinePawn::Fire()
{
	if (Cannon)
	{
		Cannon->Fire();
	}
}

void AMachinePawn::SetupCannon(TSubclassOf<ACannon> newCannonClass)
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
	Cannon->SetOwner(this);

	Cannon->AttachToComponent(CannonSetupPoint, FAttachmentTransformRules::SnapToTargetIncludingScale);
}


void AMachinePawn::BeginPlay()
{
	Super::BeginPlay();
	SetupCannon(EquippedCannonClass);
}

void AMachinePawn::Die()
{
	if (AudioEffectDie)
	{
		AudioEffectDie->Play();
	}
	if (ShootEffectDie)
	{
		ShootEffectDie->ActivateSystem();
	}
	Destroy();
	
}

void AMachinePawn::DamageTaked(float DamageValue)
{
	UE_LOG(LogTemp, Warning, TEXT("Turret %s take Damage: %f, Health: %f"), *GetName(), DamageValue, HealthComponent->GetHealth());
	
}



