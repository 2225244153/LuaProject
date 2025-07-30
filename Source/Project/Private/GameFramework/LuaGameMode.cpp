// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFramework/LuaGameMode.h"

#include "GameFramework/LuaHUD.h"
#include "GameFramework/LuaPlayerController.h"

ALuaGameMode::ALuaGameMode()
{
	ConstructorHelpers::FClassFinder<ALuaHUD> LuaHUDPath(TEXT("/Script/Engine.Blueprint'/Game/A_Game/Framework/BP_LuaHUD.BP_LuaHUD_C'"));
	if (LuaHUDPath.Succeeded())
	{
		HUDClass = LuaHUDPath.Class;
	}

	ConstructorHelpers::FClassFinder<ALuaPlayerController> LuaPlayerControllerPath(TEXT("/Script/Engine.Blueprint'/Game/A_Game/Framework/BP_LuaPlayerController.BP_LuaPlayerController_C'"));
	if (LuaPlayerControllerPath.Succeeded())
	{
		PlayerControllerClass = LuaPlayerControllerPath.Class;
	}
}
