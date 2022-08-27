// Fill out your copyright notice in the Description page of Project Settings.


#include "SSRadioButtons.h"
#include "SlateOptMacros.h"
#include "Components/VerticalBox.h"
#include <Widgets/DeclarativeSyntaxSupport.h>
#include <Widgets/SCompoundWidget.h>

#include "Widgets/Input/SCheckBox.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

//Виджет состоящий из нескольких чекбоксов и выбран одновремменно может только один чекбокс
void SSRadioButtons::Construct(const FArguments& InArgs)
{
	OnRadioButtonChanged = InArgs._OnRadioButtonChanged;
	Count = InArgs._Count;
		SetRadioButtonStyle(InArgs._Style); 
	//Передали стиль бокса
		//CheckBoxStyle = &InArgs._Style->CheckBoxStyle;
	//Передали стиль текста
		//TextStyle = &InArgs._Style->TextStyle;
	

	ChildSlot
		[
	//Макрос SAssignNew
			SAssignNew(Holder, SVerticalBox)	
		];
}

	//OnRadioButtonChanged = InArgs._OnRadioButtonChanged;
	/*ChildSlot
	[
			//С помощью макроса SNew и класса SVerticalBox создаем виджет в слейте
			//Для изменения оператора(стили и т.д.) используют оператор .
		SNew(SVerticalBox)
			//Добавляем слот через + (Add slot)
		+ SVerticalBox::Slot()
		[	//Кладем контент в слот(Виджет)
			//CreateCheckbox возвращает TSharedRef
			CreateCheckbox(0, TEXT("Option 1"))
		]
		+ SVerticalBox::Slot()
		[
			CreateCheckbox(1, TEXT("Option 2"))
		]
		+ SVerticalBox::Slot()
		[
			CreateCheckbox(2, TEXT("Option 3"))
		]
	];*/

//Аргумент срабатывает каждый тик
int32 SSRadioButtons::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry,
	const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	SCompoundWidget::OnPaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);
	if (Holder->GetChildren()->Num() == Count.Get()) return 0;
	//Каждый тик чистим слоты
	//Holder->ClearChildren();
	//Добавляем слоты
	for(int32 i = 0; i < Count.Get(); i++)
	{
		Holder->AddSlot()
		[
			CreateCheckbox(i, TEXT("Option ") + FString::FromInt(i))
		];
	}
	
	return LayerId + 1;
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
//Устанавливаем Стиль бокса и текста
	void SSRadioButtons::SetRadioButtonStyle(const FRadioButtonsStyle* InStyle)
	{
		CheckBoxStyle = &InStyle->CheckBoxStyle;
		TextStyle = &InStyle->TextStyle;
	}

/*
 * @param InIndex Индекс выбранного чекбокса
 * @param InText 
 */
TSharedRef<SWidget> SSRadioButtons::CreateCheckbox(int32 InIndex,const FString InText) const
{
	return SNew(SCheckBox)
	.IsChecked_Raw(this, &SSRadioButtons::IsChecked, InIndex)
	//При клике на другой чекбокс изменяем индекс
	//(Подписываемся на эвент, подвязываем функцию и нужно указать индекс выбранного чекбокса)
	.OnCheckStateChanged_Raw(this, &SSRadioButtons::OnCheckBoxStateChanged, InIndex)
		.Style(CheckBoxStyle)
	[
		//добавляем текст блок
		SNew(STextBlock)
		//обавляем текст 
		.Text(FText::FromString(InText))
		//Передаем указатель на текстовый стиль
			.TextStyle(TextStyle)
	];
}

/*
 * @brief 
 * @param InIndex Дополнительный агумент, Порядковый номер того чекбоска, которыс спрашивает выбран ли он
 * @return 
 */
ECheckBoxState SSRadioButtons::IsChecked(int32 InIndex) const
{
	return InIndex == CurrentIndex ? ECheckBoxState::Checked : ECheckBoxState::Unchecked;
}

/*
 * @brief 
 * @param NewState 
 * @param InIndex идекс текущего чекбокса 
 */
void SSRadioButtons::OnCheckBoxStateChanged(ECheckBoxState NewState, int32 InIndex) const
{
	//Если чекбокс выбра, то мы меняем индекс
	if(NewState == ECheckBoxState::Checked)
	{
		CurrentIndex = InIndex;
	//При создании чекбокса вызываем делегат и задаем новый индекс
		OnRadioButtonChanged.ExecuteIfBound(CurrentIndex);
	}
}

