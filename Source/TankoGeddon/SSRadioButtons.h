// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/VerticalBox.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/SCompoundWidget.h"
#include <Widgets/DeclarativeSyntaxSupport.h>

#include "RadioButtonsWidgetStyle.h"


/**
 * 
 */
//Создаем делегат
DECLARE_DELEGATE_OneParam(FOnRadioButtonChanged, int32 /*NewSelectedIndex*/)

class TANKOGEDDON_API SSRadioButtons : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSRadioButtons)
	{
	}

	SLATE_ATTRIBUTE(int32, Count);

	//передаем делегат через эвент
	SLATE_EVENT(FOnRadioButtonChanged, OnRadioButtonChanged);
	//ы передаем стиль по умолчанию или передаем наш стиль который будет использоваться
		SLATE_STYLE_ARGUMENT(FRadioButtonsStyle, Style);
	SLATE_END_ARGS()
	
	//Создаем переменную для слейт эвента
	FOnRadioButtonChanged OnRadioButtonChanged;
	
	void Construct(const FArguments& InArgs);
	
	//Этот аргумент срабатывает каждый тик
	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;
	
		void SetRadioButtonStyle(const FRadioButtonsStyle* InStyle);
	
protected:
	//стиль чекбокс передаем через указатель
		const FCheckBoxStyle* CheckBoxStyle;
	//стиль Текстблок передаем через указатель
		const FTextBlockStyle* TextStyle;
	

private:
	//Делаем массив из VerticlaBox
	TSharedPtr<SVerticalBox> Holder;
	
	//Переменная для атрибутов
	TAttribute<int32> Count;
	TSharedRef<SWidget> CreateCheckbox(int32 InIndex, FString InText) const;
	//Переменная для выбора индекса чекбокса
	mutable int32 CurrentIndex = 0;
	//Индекс выбранного чекбокса
	ECheckBoxState IsChecked(int32 InIndex) const;

	void OnCheckBoxStateChanged(ECheckBoxState NewState, int32 InIndex) const;

		
};