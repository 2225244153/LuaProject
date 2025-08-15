// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScrollBoxIntoViewUserWidget.generated.h"

class UButton;
class UScrollBox;
/**
 * 
 */
UCLASS()
class PROJECT_API UScrollBoxIntoViewUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual void NativeConstruct() override;

public:
	UPROPERTY(meta = (BindWidget))
	UScrollBox* ScrollBox_Button;
	
};
