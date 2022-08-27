// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PrimitiveComponent.h"
#include "GameStruct.h"
#include "DamageTaker.h"
#include "Particles/ParticleSystemComponent.h"
#include "TimerManager.h"

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
	
	ShootEffectProjectile = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ShootEffectProjectile"));
	ShootEffectProjectile->SetupAttachment(ProjectileMesh);

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

void AProjectile::ExplodeProject()
{
	FVector startPos = GetActorLocation();
	FVector endPos = startPos + FVector(0.1f);

	FCollisionShape Shape = FCollisionShape::MakeSphere(ProjectileRadius);
	FCollisionQueryParams params = FCollisionQueryParams::DefaultQueryParam;
	params.AddIgnoredActor(this);
	params.bTraceComplex = true;
	params.TraceTag = "Explode Trace";

	TArray<FHitResult> AttachHit;

	FQuat Rotation = FQuat::Identity;

	bool bSweepResult = GetWorld()->SweepMultiByChannel(AttachHit, startPos, endPos, Rotation, ECollisionChannel::ECC_Visibility, Shape, params);

	
	DrawDebugSphere(GetWorld(), startPos, ProjectileRadius, 5, FColor::Green, false, 2.0f);

	if (bSweepResult)
	{
		for (FHitResult hitResult : AttachHit)
		{
			AActor* otherActor = hitResult.GetActor();
			if (!otherActor)
			{
				continue;
			}
			IDamageTaker* DamageTakerActor = Cast<IDamageTaker>(otherActor);
			if (DamageTakerActor)
			{
				DamageDataHP(DamageTakerActor, Owner);
			}
			else
			{
				UPrimitiveComponent* mesh = Cast<UPrimitiveComponent>(otherActor->GetRootComponent());
				if (mesh)
				{
					if (mesh->IsSimulatingPhysics())
					{
							AddForcePhysic(otherActor, mesh);
					}
				}

			}
		}
	}
}





void AProjectile::AddForcePhysic(AActor* otherActor, UPrimitiveComponent* mesh)
{
	
	FVector forceVector = otherActor->GetActorLocation() - GetActorLocation();
	forceVector.Normalize();
	mesh->AddForce(forceVector * PushForce, NAME_None, true);
}

					
void AProjectile::DamageDataHP(IDamageTaker* DamageTakerActor, AActor* owner)
{
	FDamageData damageData;
	damageData.DamageValue = Damage;
	damageData.Instigator = owner;
	damageData.DamageMaker = this;

	DamageTakerActor->TakeDamage(damageData);
}


void AProjectile::OnMeshOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Outputting an intersection with an object to the console
	//UE_LOG(LogTemp, Warning, TEXT("Projectile collided with %s, collided with component %s"), *OtherActor->GetName(), *OverlappedComp->GetName());

	//Проверка актора на получения урона
	AActor* owner = GetOwner();
	AActor* ownerByOwner = owner != nullptr ? owner->GetOwner() : nullptr;

	if (OtherActor != owner && OtherActor != ownerByOwner)
	{
		IDamageTaker* DamageTakerActor = Cast<IDamageTaker>(OtherActor);
		if (DamageTakerActor)
		{
			DamageDataHP(DamageTakerActor, owner);

			if (bEnabelExplode)
			{
				ExplodeProject();
			}
		}
		else
		{
			UPrimitiveComponent* mesh = Cast<UPrimitiveComponent>(OtherActor->GetRootComponent());
			if (mesh)
			{
				if (mesh->IsSimulatingPhysics())
				{
					AddForcePhysic(OtherActor, mesh);
					if (bEnabelExplode)
					{
						ExplodeProject();
					}
				}
			}
			
		}
		if (bEnabelExplode)
			ExplodeProject();
		ShootEffectProjectile->ActivateSystem();
		Destroy();
	}
}

