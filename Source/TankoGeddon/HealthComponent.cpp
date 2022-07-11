// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"


void UHealthComponent::TakeDamage(FDamageData DamageData)//ћетод получени€ урона
{
	float takeDamageValue = DamageData.DamageValue; //получаем значени€ нанесенного нам урона

	CurrentHealth -= takeDamageValue;

	if (CurrentHealth <= 0.0f)//≈сли наш урон меньше 0 вызываем два метода на смерть
	{
		if (OnDie.IsBound())//ќповещают игрока что он умер
			OnDie.Broadcast();//ќповещают игрока что он умер
	}
	else //если игрок не умирает
	{
		if (OnHealthChanged.IsBound())		//≈сли здоровь€ больше 0 то оповещаем игрока что он получил урон
			OnHealthChanged.Broadcast(takeDamageValue); //вызываем все методы которые на него подписаны и передаст им значение
	}
}

float UHealthComponent::GetHealth() const
{
	return CurrentHealth;

}

float UHealthComponent::GetHealthState() const
{
	return CurrentHealth / MaxHealth;

}

void UHealthComponent::AddHealth(float AddHealthValue)
{
	CurrentHealth += AddHealthValue;
	if (CurrentHealth > MaxHealth)
	{
		CurrentHealth = MaxHealth;
	}
}
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;

}




