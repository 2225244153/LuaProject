// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFramework/LuaHUD.h"


#include "UMG/Main/MainUserWidget.h"

/*ALuaHUD::ALuaHUD()
{
	
}*/

void ALuaHUD::BeginPlay()
{
	Super::BeginPlay();
	
	GetOwningPlayerController()->SetShowMouseCursor(true);
	
	 TSubclassOf<UMainUserWidget>MainUIClass  = LoadClass<UMainUserWidget>(nullptr,
	 	TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/A_Game/UMG/MainUI/WBP_MainUI.WBP_MainUI_C'"));
	if (MainUIClass)
	{
		MainUIWidget = CreateWidget<UMainUserWidget>(GetOwningPlayerController(), MainUIClass);
		MainUIWidget->AddToViewport();
		//MainUIWidget->AddToPlayerScreen(0)
	}
	
}
