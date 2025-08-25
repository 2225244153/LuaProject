// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/List/ListItemWidget.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "UMG/List/ListWidget.h"
#include "UMG/Object/TestListViewObject.h"

void UListItemWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ListItemButton->OnClicked.AddDynamic(this,&UListItemWidget::ButtonClick);
}

void UListItemWidget::ButtonClick()
{
	OwnerWidget->RefreshList(Index);
}

void UListItemWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	UTestListViewObject* TestListViewObject = Cast<UTestListViewObject>(ListItemObject);
	if (TestListViewObject != nullptr)
	{
		ListItemImage->SetBrushFromTexture(TestListViewObject->Image);
		Index = TestListViewObject->Index;
		OwnerWidget = Cast<UListWidget>(TestListViewObject->OwnerWidget);
		SetSelectedState(TestListViewObject->bSelected);
	}
}

void UListItemWidget::SetSelectedState(bool bSelected)
{
	if (bSelected)
	{
		ListItemImage->SetColorAndOpacity(FLinearColor::Black);
	}
	else
	{
		ListItemImage->SetColorAndOpacity(FLinearColor::White);
	}
}


