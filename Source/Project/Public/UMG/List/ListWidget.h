// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ListWidget.generated.h"

class UTestListViewObject;
class UListView;
class URetainerBox;
/**
 * 
 */
UCLASS()
class PROJECT_API UListWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual void NativePreConstruct() override;
	
public:

	UPROPERTY(meta = (BindWidget))
	URetainerBox* MainRetainerBox;

	UPROPERTY(meta = (BindWidget))
	UListView* MainListView;

	void SetListViewData();
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TArray<UTexture2D*> ListTextures;
	
};
