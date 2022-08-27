// Fill out your copyright notice in the Description page of Project Settings.


#include "RadioButtonsWidgetStyle.h"

#include "MyCoreStyle.h"

// конструкторе нашего стиля задали значения для чекбокс и текст стиля(чтобы у нас все выглядело нормально из коробки и не разваливалось)
FRadioButtonsStyle::FRadioButtonsStyle()
{
	CheckBoxStyle = FCoreStyle::Get().GetWidgetStyle<FCheckBoxStyle>("RadioButton");
	TextStyle = FCoreStyle::Get().GetWidgetStyle<FTextBlockStyle>("NormalUnderLinedText");
	
}

FRadioButtonsStyle::~FRadioButtonsStyle()
{
}

const FName FRadioButtonsStyle::TypeName(TEXT("FRadioButtonsStyle"));

const FRadioButtonsStyle& FRadioButtonsStyle::GetDefault()
{
	static FRadioButtonsStyle Default;
	return Default;
}

void FRadioButtonsStyle::GetResources(TArray<const FSlateBrush*>& OutBrushes) const
{
	//При использовании виртуальнй функции в ее теле мы вызываем родительскую функцию
	FSlateWidgetStyle::GetResources(OutBrushes);

	//Загружаем чекбоксстиль и текс стиль (вызываем фу-ю get и передаем параметр через ссылку
	CheckBoxStyle.GetResources(OutBrushes);
	TextStyle.GetResources(OutBrushes);
}

