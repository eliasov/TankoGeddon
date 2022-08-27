// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSRadioButtons.h"
#include "Components/Widget.h"
#include "RadioButtons.generated.h"

class SSRadioButtons;

//Создаем делегат который будет находится в UMG иджете
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRadioButtonChangedEvent, int32, NewSelectedButton);

UCLASS()
class TANKOGEDDON_API URadioButtons : public UWidget
{
	GENERATED_BODY()

public:
#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override {return FText::FromString(TEXT("Input"));};
#endif
	

	
	UPROPERTY(BlueprintAssignable)
	FOnRadioButtonChangedEvent OnRadioButtonChanged;

		UPROPERTY(EditAnywhere, Category= Appearance, meta=(DisplayName="Style"))
		FRadioButtonsStyle WidgetStyle;
	//Эту переменную можем задать в BP
	UPROPERTY(EditAnywhere)
	int32 Count;
	//Begin Interface UVisual
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
	//End Interface UVisual

protected:
	//Begin Interface UVisual
	virtual TSharedRef<SWidget> RebuildWidget() override;
	//End Interface UVisual

	
private:
	
	TSharedPtr<SSRadioButtons> RadioButtons;
	int32 GetCount() const {return Count; };
	//Функция с сигнатурой как у нашего делегата в SSRadioButton
	void OnRadioButtonsChangedFunc(int32 NewSelectedButton);
};
