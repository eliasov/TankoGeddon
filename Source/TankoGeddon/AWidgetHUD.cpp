// Fill out your copyright notice in the Description page of Project Settings.


#include "AWidgetHUD.h"

#include "Blueprint/WidgetBlueprintLibrary.h"

void AAWidgetHUD::BeginPlay()
{
	Super::BeginPlay();

	if(GetWorld())
	{
		APlayerController * PC = GetWorld()->GetFirstPlayerController();
		if(PC)
		{
			UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(PC, nullptr, EMouseLockMode::DoNotLock, false);
			PC->bShowMouseCursor = true;
		}
	}
}

void AAWidgetHUD::RemoveCurrentWidgetFromViewport()
{
	if (CurrentWidget)
	{
		CurrentWidget->RemoveFromParent();
		CurrentWidget = nullptr;
		CurrentWidgetID = EWidgetID::None;
	}
}
UUserWidget* AAWidgetHUD::AddWidgetToViewportByClass(TSubclassOf<UUserWidget> WidgetClass, int32 ZOrder)
{
	CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);
	if (CurrentWidget)
	{
		CurrentWidget->AddToViewport(ZOrder);
	}
	return CurrentWidget;
}


UUserWidget* AAWidgetHUD::UseWidget(EWidgetID widgetID, bool RemovePrevious, int32 ZOrder)
{
	if (CurrentWidgetID == widgetID) return CurrentWidget;
	if (RemovePrevious)
	{
		RemoveCurrentWidgetFromViewport();
	}
	TSubclassOf<UUserWidget> WidgetClassToUse = WidgetClases.FindRef(widgetID);
	if (WidgetClassToUse.Get())
	{
		CurrentWidgetID = widgetID;
		return AddWidgetToViewportByClass(WidgetClassToUse, ZOrder);
	};
	return nullptr;
}


UUserWidget* AAWidgetHUD::GetCurrentWidget()
{
	return CurrentWidget;
}






