// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannon.h"
#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components\SceneComponent.h"
#include "Projectile.h"
#include "DrawDebugHelpers.h"
#include "DamageTaker.h"

// Sets default values
ACannon::ACannon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* CannonSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("CannonRoot"));
	RootComponent = CannonSceneComponent;

	CannonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CannonMesh"));
	CannonMesh->SetupAttachment(CannonSceneComponent);

	ProjectileSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("ProjectileSpawnPoint"));
	ProjectileSpawnPoint->SetupAttachment(CannonSceneComponent);
}

void ACannon::Fire()
{
	//cannon fire test
	if (!bCanFire)
	{
		GEngine->AddOnScreenDebugMessage(10, 1, FColor::Red, "Reload");
		return;
	}
	if (WhizBang <= 0)
	{
		GEngine->AddOnScreenDebugMessage(10, 1, FColor::Red, "Reload");
		return;
	}
	
	bCanFire = false;
	WhizBang--;
	
	if (CannonType == ECannonType::FireProjectile)
	{
		if (!fireTextTurrent)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Fire projectile ")));
			if (!fireTextTurrent)
			{
				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Bullet = %d"), WhizBang));
			}
		}
		
			//Projectile firing implementation
		if (ProjectilePool)
		{
			ProjectilePool->GetProjectile(ProjectileSpawnPoint->GetComponentLocation(), ProjectileSpawnPoint->GetComponentRotation());
		}
		else {
			AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnPoint->GetComponentLocation(), ProjectileSpawnPoint->GetComponentRotation());

			if (projectile)
			{
					projectile->SetOwner(this);
					projectile->Start();
			}
		}
	}

	else
	{	
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Fire trace ")));
			FHitResult hitResult;
			FCollisionQueryParams traceParams = FCollisionQueryParams(FName(TEXT("FireTrace")), true, this);
				traceParams.bTraceComplex = true;
				traceParams.bReturnPhysicalMaterial = false;
			

			FVector StartTrace = ProjectileSpawnPoint->GetComponentLocation();
			FVector EndTrace = StartTrace + ProjectileSpawnPoint->GetForwardVector() * FireRange;
		

				if (GetWorld()->LineTraceSingleByChannel(hitResult, StartTrace, EndTrace, ECollisionChannel::ECC_Visibility, traceParams))
				{
					DrawDebugLine(GetWorld(), StartTrace, hitResult.Location, FColor::Red, false, 0.5f, 0, 10);
					AActor* owner = GetOwner();
					AActor* OtherActor = hitResult.GetActor();

					if (OtherActor)
					{
						IDamageTaker* damageTakerActor = Cast<IDamageTaker>(OtherActor);

						if (damageTakerActor)
						{
							FDamageData damageData;
							damageData.DamageValue = 10;
							damageData.Instigator = owner;
							damageData.DamageMaker = this;

							damageTakerActor->TakeDamage(damageData);
						}
						else
						{
							OtherActor->Destroy();
						}
						void Deactivate();
					}
				}
				else
				{
					DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Purple, false, 0.5f, 0, 10);
				}
				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Bullet = %d"), WhizBang));
	}
	
	GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &ACannon::Reload, ReloadTime, false);
}

	


void ACannon::FireSpecial()
{
	
	if (!bCanFire || WhizBang <= 0)
	{

		GEngine->AddOnScreenDebugMessage(10, 1, FColor::Red, "Reload");
		return;
	}

	bCanFire = false;
	Bang();
}
void ACannon::Reload()
{
	bCanFire = true;
}

void ACannon::CreateProjectilePool()
{
	if (ProjectilePoolClass)
		ProjectilePool = GetWorld()->SpawnActor<AProjectilePool>(ProjectilePoolClass, 
		ProjectileSpawnPoint->GetComponentLocation(), ProjectileSpawnPoint->GetComponentRotation());
}

void ACannon::Deactivate()
{
	bIsActivation = false;										//Наш объект не активен
	SetActorLocation(FVector(0.0f, 0.0f, -50.0f));				//Перемещаем объект в невидимую позицию
	GetWorld()->GetTimerManager().ClearTimer(DeactivateTimer);	//Отключаем таймер 
	GetWorld()->GetTimerManager().ClearTimer(MoveTimer);		//Отключаем таймер на движение
	SetActorEnableCollision(false);								//Отключаем коллизию
}

void ACannon::BeginPlay()
{
	Super::BeginPlay();
}

void ACannon::Bang()
{
	if (ActualBang == BangSize)
	{
		GetWorld()->GetTimerManager().ClearTimer(BangTimer);
		bCanFire = true;
		ActualBang = 0;
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Bullet = %d"), WhizBang));
		return;
	}
	ActualBang++;
	if (CannonType == ECannonType::FireProjectile)
	{
		
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Black, FString::Printf(TEXT("Fire Projectile")));
		AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnPoint->GetComponentLocation(), ProjectileSpawnPoint->GetComponentRotation());
		if (projectile)
		{
			if (WhizBang > 0)
				projectile->Start();
			WhizBang--;
		}
		
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Purple, FString::Printf(TEXT("Fire trace")));
	}
	GetWorld()->GetTimerManager().SetTimer(BangTimer, this, &ACannon::Bang, BangInterval, false);
}






