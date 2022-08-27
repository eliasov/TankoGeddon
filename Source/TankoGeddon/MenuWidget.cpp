// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"

#include "MyCoreStyle.h"
#include "SSRadioButtons.h"
#include "Components/Button.h"




//Subscribe NewGameButton

void UMenuWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if(LevelSelectButtons)
	{
		LevelSelectButtons->WidgetStyle = FMyCoreStyle::Get().GetWidgetStyle<FRadioButtonsStyle>("WS_RadioButtons_Default");
	}
	
}

void UMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if(NewGameBtn)
	{
		NewGameBtn->OnPressed.AddDynamic(this, &ThisClass::OnNewGameClicked);
	}
	if(QuitBtn)
	{
		QuitBtn->OnPressed.AddDynamic(this, &ThisClass::OnQuitClicked);
	}
	//Если есть виджет хотс
	if(RadioButtonsHost)
	{
		//Мы ему устанавливам Контент
		RadioButtonsHost->SetContent(SNew(SSRadioButtons));
	}
}


//Unsubscribe NewGameButton when destroyed
void UMenuWidget::NativeDestruct()
{
	Super::NativeDestruct();

	if(NewGameBtn)
	{
		NewGameBtn->OnPressed.RemoveAll(this);
	}
	if(QuitBtn)
	{
		QuitBtn->OnPressed.RemoveAll(this);
	}
}

void UMenuWidget::OnNewGameClicked()
{
	if(NewGameAnimation)
	{
		PlayAnimation(NewGameAnimation);
	}
	OneButtonSelected.Broadcast(0);
}

void UMenuWidget::OnQuitClicked()
{
	//GEngine->Exec(GetWorld(), TEXT("Quit"));
	OneButtonSelected.Broadcast(1);
}
