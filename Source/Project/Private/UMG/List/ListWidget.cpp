// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/List/ListWidget.h"

#include "K2Node_ConstructObjectFromClass.h"
#include "Components/ListView.h"
#include "UMG/Object/TestListViewObject.h"

void UListWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	MainListView->SetScrollbarVisibility(ESlateVisibility::Collapsed);

	
}

void UListWidget::SetListViewData()
{
	MainListView->ClearListItems();
	for (int32 Index = 0; Index < ListTextures.Num(); Index++)
	{
		if (UTestListViewObject* TestListViewObject = NewObject<UTestListViewObject>(UTestListViewObject::StaticClass()))
		{
			TestListViewObject->Image = ListTextures[Index];
			TestListViewObject->Index = Index;
			TestListViewObject->OwnerWidget = this;
			MainListView->AddItem(TestListViewObject);
		}
	}
}

