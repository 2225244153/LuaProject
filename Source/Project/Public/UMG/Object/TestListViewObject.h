// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "TestListViewObject.generated.h"

class UListWidget;
/**
 * 
 */
UCLASS()
class PROJECT_API UTestListViewObject : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	UTexture2D* Image;

	UPROPERTY()
	int32 Index;

	UPROPERTY()
	UListWidget* OwnerWidget;
	
};
