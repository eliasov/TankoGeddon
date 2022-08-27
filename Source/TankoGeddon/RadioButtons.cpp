// Fill out your copyright notice in the Description page of Project Settings.


#include "RadioButtons.h"

#include "Widgets/Layout/SSpacer.h"

void URadioButtons::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);
	//брос умного указателя
	RadioButtons.Reset();
}

TSharedRef<SWidget> URadioButtons::RebuildWidget()
{
	//Записываем в переменную RadioButtons данные
	RadioButtons = SNew(SSRadioButtons)
	.Count_UObject(this, &ThisClass::GetCount)
	//Передаем idgrtStyle внутрь слейд виджета
		.Style(&WidgetStyle)
	//Подписываемся на делегат и Задаем параметры
	.OnRadioButtonChanged_UObject(this, &ThisClass::OnRadioButtonsChangedFunc);
	
	
	//возвращаем SharedRef с типом данных sharedRef
	//Если у пользователя закончилась память (Перестраховка)
	//return RadioButtons.IsValid() ? RadioButtons.ToSharedRef() : SNew(SSpacer);
	return RadioButtons.ToSharedRef();
}

void URadioButtons::OnRadioButtonsChangedFunc(int32 NewSelectedButton)
{
	//Внутри UMG виджета вызываем делешат
	OnRadioButtonChanged.Broadcast(NewSelectedButton);
}
