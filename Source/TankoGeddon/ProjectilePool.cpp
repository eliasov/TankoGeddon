// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectilePool.h"
#include "Projectile.h"



void AProjectilePool::GetProjectile(FVector spawnLocation, FRotator spawnRotation)
{
	bHaveActiveProjectile = false;
	for (int32 i = 0; i < ProjectilePool.Num(); i++)
	{
		if (ProjectilePool[i]->bIsActivation == false)
		{
			ProjectilePool[i]->SetActorLocation(spawnLocation);//установили местоположения
			ProjectilePool[i]->SetActorRotation(spawnRotation);//установили вращение
			ProjectilePool[i]->bIsActivation = true;//Задаем что снаряд активный
			bHaveActiveProjectile = true;//Задаем что мы нашли активный снаряд
			ProjectilePool[i]->SetActorEnableCollision(true);//включаем колюзию
			ProjectilePool[i]->Start();//Задаем старт снаряда
			return;//выходим 
		}
	}
	if (bHaveActiveProjectile == false)//Если снаряд не нашли мы создаем новый
	{
		SpawnProjectile(spawnLocation, spawnRotation, true);//Делаем снаряд активным
	}

}

// Called when the game starts or when spawned
void AProjectilePool::BeginPlay()
{
	Super::BeginPlay();

	InitializePool();
	
}

void AProjectilePool::SpawnProjectile(FVector SpawnLocation, FRotator SpawnRotation, bool bIsActive)
{
	AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);

	if (projectile)
	{
		ProjectilePool.Add(projectile);//Если спавн снаряда произошел успешно мы добавляем снаряд в пул
		projectile->bIsActivation = bIsActive;//Активен этот снаряд или нет
		projectile->SetActorEnableCollision(bIsActive);//отключения колизии у снаряда перед спавном
		
		if (bIsActive)//если она тру наш проджектайл движется
		{
			projectile->Start();
		}
	}
}

void AProjectilePool::InitializePool()
{
	for (int32 i = 0; i < PoolSize; i++)
	{
		SpawnProjectile(FVector(0.0f, 0.0f, 0.0f), FRotator(0.0f, 0.0f, 0.0f));
	}
}


