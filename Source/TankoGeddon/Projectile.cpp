// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PrimitiveComponent.h"
#include "GameStruct.h"
#include "DamageTaker.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	//Stage placement component
	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = SceneComponent;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjecttileMesh"));
	ProjectileMesh->SetupAttachment(SceneComponent);

	//Subscribe to a method AProjectile::OnMeshOverlapBegin
	ProjectileMesh->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnMeshOverlapBegin);

	ProjectileMesh->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
	


}


//projectile movement timer
void AProjectile::Start()
{
	GetWorld()->GetTimerManager().SetTimer(MoveTimer, this, &AProjectile::Move, MoveRate, true, MoveRate);
	GetWorld()->GetTimerManager().SetTimer(DeactivateTimer, this, &AProjectile::Deactivate, DeactivateTime, false);
}

void AProjectile::Deactivate()
{
	bIsActivation = false;										//Наш объект не активен
	SetActorLocation(FVector(0.0f, 0.0f, -50.0f));				//Перемещаем объект в невидимую позицию
	GetWorld()->GetTimerManager().ClearTimer(DeactivateTimer);	//Отключаем таймер 
	GetWorld()->GetTimerManager().ClearTimer(MoveTimer);		//Отключаем таймер на движение
	SetActorEnableCollision(false);								//Отключаем коллизию
}

//The movement of the projectile in the direction of travel
void AProjectile::Move()
{
	FVector nextPosition = GetActorLocation() + GetActorForwardVector() * MoveSpeed * MoveRate;
	SetActorLocation(nextPosition);
}

void AProjectile::OnMeshOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Outputting an intersection with an object to the console
	UE_LOG(LogTemp, Warning, TEXT("Projectile collided with %s, collided with component %s"), *OtherActor->GetName(), *OverlappedComp->GetName());
	
	//Проверка актора на получения урона
	AActor* owner = GetOwner();
	if (owner)
	{
		UE_LOG(LogTemp, Warning, TEXT("Owner is %s"), *owner->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Owner is null"));
	}
	
	AActor* ownerByOwner = owner != nullptr ? owner->GetOwner() : nullptr;
	if (ownerByOwner)
	{
		UE_LOG(LogTemp, Warning, TEXT("OwnerByOwner is %s"), *ownerByOwner->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Owner is null"));
	}
		

	if (OtherActor != owner && OtherActor != ownerByOwner)
	{
		IDamageTaker* damageTakerActor = Cast<IDamageTaker>(OtherActor);
		if (damageTakerActor)
		{
			FDamageData damageData;
			damageData.DamageValue = Damage;
			damageData.Instigator = owner;
			damageData.DamageMaker = this;

			damageTakerActor->TakeDamage(damageData);
		}
		else
		{
			OtherActor->Destroy();
		}
		Deactivate();
	}
}



