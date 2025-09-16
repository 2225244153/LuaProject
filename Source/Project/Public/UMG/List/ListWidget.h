// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ListWidget.generated.h"

class UListItemWidget;
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

	virtual void NativeOnInitialized() override;
	
	void OnListViewScrolled(float X, float Arg);
	
	
	void OnEntryWidgetReleased(UUserWidget& UserWidget);

	UPROPERTY()
	UListItemWidget* ListItemWidget;
	
public:

	
	UPROPERTY(BlueprintReadWrite,EditAnywhere,meta = (BindWidget))
	UListView* MainListView;

	UPROPERTY()
	int32 SelectedIndex = 0;

	UFUNCTION(BlueprintCallable)
	void SetListViewData();
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TArray<UTexture2D*> ListTextures;

	void RefreshList(int32 Index);

	void ChangeSelectedState(int32 OldIndex,int32 NewIndex);

	
	
};
