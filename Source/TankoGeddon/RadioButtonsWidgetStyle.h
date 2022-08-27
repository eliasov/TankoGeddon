// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateTypes.h"
#include "Styling/SlateWidgetStyle.h"
#include "Styling/SlateWidgetStyleContainerBase.h"
#include "RadioButtonsWidgetStyle.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct TANKOGEDDON_API FRadioButtonsStyle : public FSlateWidgetStyle
{
	GENERATED_USTRUCT_BODY()

	FRadioButtonsStyle();
	virtual ~FRadioButtonsStyle();

	//Стиль для чекбокса
	UPROPERTY(EditAnywhere, Category = Appearance)
    FCheckBoxStyle CheckBoxStyle;
	
    //Стиль для текста
    UPROPERTY(EditAnywhere, Category = Appearance)
    FTextBlockStyle TextStyle;
//Чтобы стиль работал его нужно применить. Для этого он должен начинаться со слейтовского стиля.
	
	

	// FSlateWidgetStyle
	//Получает параметром массив слейт-брашей.
	virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;
	static const FName TypeName;
	//Возвращает название типа, можно не изменять.
	virtual const FName GetTypeName() const override { return TypeName; };
	//возвращает стандартный стиль. Именно там можно проинициализировать свойства
	//стиля стандартными значениями, если нужно.
	static const FRadioButtonsStyle& GetDefault();
};

/**
 Создание ассета стиля в content браузере
 */

UCLASS(hidecategories=Object, MinimalAPI)
class URadioButtonsWidgetStyle : public USlateWidgetStyleContainerBase
{
	GENERATED_BODY()

public:
	/** The actual data describing the widget appearance. */
	UPROPERTY(Category=Appearance,EditAnywhere, meta=(ShowOnlyInnerProperties))
	FRadioButtonsStyle WidgetStyle;

	virtual const struct FSlateWidgetStyle* const GetStyle() const override
	{
		return static_cast< const struct FSlateWidgetStyle* >( &WidgetStyle );
	}
};
