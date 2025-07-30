// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "LuaHUD.generated.h"

class UMainUIWidget;
/**
 * 
 */
UCLASS()
class PROJECT_API ALuaHUD : public AHUD
{
	GENERATED_BODY()

protected:
	/*/*#1#ALuaHUD();
	*/

virtual void BeginPlay() override;

public:
	UPROPERTY()
	UMainUIWidget* MainUIWidget;
	
};
