// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AWidgetHUD.generated.h"

/**
 * 
 */

UENUM()
enum class EWidgetID : uint8
{
	None,
	Continue,
	MainMenu,
	PauseMenu,
	PauseMenuToWidgetMenu,
	LoadingScreen,
	HealthBar,
	GameOver
};

UCLASS()
class TANKOGEDDON_API AAWidgetHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	void RemoveCurrentWidgetFromViewport();

	UFUNCTION(BlueprintCallable)
	UUserWidget * AddWidgetToViewportByClass(TSubclassOf<UUserWidget> WidgetClass, int32 ZOrder = 0);

	UFUNCTION(BlueprintCallable)
	UUserWidget * UseWidget(EWidgetID widgetID, bool RemovePrevious = true, int32 ZOrder = 0);
	
	UFUNCTION(BlueprintCallable)
	UUserWidget * GetCurrentWidget();
	
protected:

	//UUserWidget* CreateWidgetByClass(const TSubclassOf<UUserWidget> WidgetClass, const int32 ZOrder = 0);
	
	UPROPERTY(EditAnywhere)
	TMap<EWidgetID, TSubclassOf<UUserWidget>> WidgetClases;

	UPROPERTY()
	UUserWidget * CurrentWidget;

	EWidgetID CurrentWidgetID;
};
