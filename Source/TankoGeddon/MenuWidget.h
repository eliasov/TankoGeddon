// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RadioButtons.h"
#include "Blueprint/UserWidget.h"
#include "Components/ListView.h"
#include "Components/NativeWidgetHost.h"
#include "MenuWidget.generated.h"

/**
 * 
 */

class UButton;

//Delegate
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMainMenuDelegate, int32, SelectedButton);

UCLASS()
class TANKOGEDDON_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativePreConstruct() override;
	//Function constuctor(Begin play actor)
	virtual void NativeConstruct() override;
	//Function destructor(End play actor)
	virtual void NativeDestruct() override;
	
	
	

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
	UButton *NewGameBtn;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetAnim), Transient)
	UWidgetAnimation *NewGameAnimation;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
	UButton *LoadBtn;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
	UButton *OptionsBtn;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
	UButton *QuitBtn;

	UPROPERTY(BlueprintAssignable)
	FMainMenuDelegate OneButtonSelected;

	UFUNCTION()
	void OnNewGameClicked();

	UFUNCTION()
	void OnQuitClicked();

	//это виджет-контейнер, который может содержать один дочерний виджет планшета.
	//Это следует использовать, когда все, что вам нужно, это вложить собственный виджет в виджет UMG.
	UPROPERTY(BlueprintReadOnly, meta =(BindWidgetOptional))
	UNativeWidgetHost* RadioButtonsHost;

	UPROPERTY(meta = (BindWidgetOptional))
    URadioButtons * LevelSelectButtons;

};