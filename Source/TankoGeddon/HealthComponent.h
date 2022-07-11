// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameStruct.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKOGEDDON_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

	//Создаем два эвента(Событие на смерть и событие на получение урона урон)
	DECLARE_EVENT(UHealthComponent, FOnDie);
	DECLARE_EVENT_OneParam(UHealthComponent, FOnHealthChanged, float);

public:	
	
	FOnDie OnDie;
	FOnHealthChanged OnHealthChanged;


	//Метод нанесения урона
	void TakeDamage(FDamageData DamageData);

	//метод получения состояния здоровья
	float GetHealth() const;

	//метод получения состояния здоровья
	float GetHealthState() const;

	//Метод получения здоровья
	void AddHealth(float AddHealthValue);

protected:
	
	virtual void BeginPlay() override;

public:	
	
	//Максимальное здоровье
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth = 25.0f;
	//Текущее здоровье
	UPROPERTY()
	float CurrentHealth;
};
