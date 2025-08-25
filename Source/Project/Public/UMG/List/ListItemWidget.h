// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "ListItemWidget.generated.h"

class UListWidget;
class UImage;
class UButton;
/**
 * 
 */
UCLASS()
class PROJECT_API UListItemWidget : public UUserWidget, public IUserObjectListEntry 
{
	GENERATED_BODY()

protected:

	virtual void NativeOnInitialized() override;

	UFUNCTION()
	void ButtonClick();

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	void SetSelectedState(bool bSelected);
public:

	UPROPERTY(meta = (BindWidget))
	UButton* ListItemButton;

	UPROPERTY(meta = (BindWidget))
	UImage* ListItemImage;

	UPROPERTY()
	int32 Index;

	UPROPERTY()
	UListWidget* OwnerWidget;



	
	
};
