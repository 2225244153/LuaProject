// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/List/ListWidget.h"
#include "Components/ListView.h"
#include "UMG/List/ListItemWidget.h"
#include "UMG/Object/TestListViewObject.h"

void UListWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	MainListView->SetScrollbarVisibility(ESlateVisibility::Collapsed);
	MainListView->OnListViewScrolled().AddUObject(this,&UListWidget::OnListViewScrolled);
}

void UListWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UListWidget::OnListViewScrolled(float Offset, float Arg)
{
	
}

void UListWidget::OnEntryWidgetReleased(UUserWidget& UserWidget)
{
}

void UListWidget::RefreshList(int32 Index)
{
	ChangeSelectedState(SelectedIndex,Index);
	SelectedIndex = Index;
	MainListView->NavigateToIndex(Index);
}

void UListWidget::ChangeSelectedState(int32 OldIndex, int32 NewIndex)
{
	UTestListViewObject* OldObject = Cast<UTestListViewObject>(MainListView->GetItemAt(OldIndex));
	OldObject->bSelected = false;
	UTestListViewObject* NewObject = Cast<UTestListViewObject>(MainListView->GetItemAt(NewIndex));
	NewObject->bSelected = true;
	MainListView->RequestRefresh();
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
			TestListViewObject->bSelected = SelectedIndex == Index;
			MainListView->AddItem(TestListViewObject);
		}
	}
}



