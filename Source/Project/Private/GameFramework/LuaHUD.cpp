// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFramework/LuaHUD.h"

#include "UMG/MainUIWidget.h"

/*ALuaHUD::ALuaHUD()
{
	
}*/

void ALuaHUD::BeginPlay()
{
	Super::BeginPlay();
	
	GetOwningPlayerController()->SetShowMouseCursor(true);
	
	 TSubclassOf<UMainUIWidget>MainUIClass  = LoadClass<UMainUIWidget>(nullptr,
	 	TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/A_Game/UMG/WBP_MainUI.WBP_MainUI_C'"));
	if (MainUIClass)
	{
		MainUIWidget = CreateWidget<UMainUIWidget>(GetOwningPlayerController(), MainUIClass);
		MainUIWidget->AddToViewport();
		//MainUIWidget->AddToPlayerScreen(0)
	}
	
}
