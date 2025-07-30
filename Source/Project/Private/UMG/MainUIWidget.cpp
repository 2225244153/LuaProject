// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/MainUIWidget.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/WidgetSwitcher.h"
#include "Kismet/KismetSystemLibrary.h"

void UMainUIWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	BindButtons();
}

void UMainUIWidget::BindButtons()
{
	MainUIButton->OnClicked.AddDynamic(this,&UMainUIWidget::MainUIButtonClicked);
	MainUIButton->OnHovered.AddDynamic(this,&UMainUIWidget::MainUIButtonHovered);
	MainUIButton->OnUnhovered.AddDynamic(this,&UMainUIWidget::MainUIButtonUnhovered);
}


void UMainUIWidget::MainUIButtonClicked()
{
	UKismetSystemLibrary::PrintString(nullptr,"MainUIButtonClick");
}

void UMainUIWidget::MainUIButtonHovered()
{
	//Image_Hover->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	Switcher_Type->SetActiveWidgetIndex(0);
}

void UMainUIWidget::MainUIButtonUnhovered()
{
	//Image_Hover->SetVisibility(ESlateVisibility::Collapsed);
	Switcher_Type->SetActiveWidgetIndex(1);
}
