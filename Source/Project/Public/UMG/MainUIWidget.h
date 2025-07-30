// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainUIWidget.generated.h"

class UWidgetSwitcher;
class UImage;
class UButton;
/**
 * 
 */
UCLASS()
class PROJECT_API UMainUIWidget : public UUserWidget
{
	GENERATED_BODY()
protected:

	virtual void NativeOnInitialized() override;

	void BindButtons();

	UFUNCTION()
	void MainUIButtonClicked();

	UFUNCTION()
	void MainUIButtonHovered();

	UFUNCTION()
	void MainUIButtonUnhovered();

	
	
public:
	UPROPERTY(meta = (BindWidget))
	UButton* MainUIButton;

	UPROPERTY(meta = (BindWidget))
	UImage* Image_Hover;

	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* Switcher_Type;
};
