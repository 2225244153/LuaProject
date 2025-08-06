// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestActor.generated.h"

USTRUCT()
struct FMyTest
{
	GENERATED_BODY()

	UPROPERTY()
	int32 X;
	UPROPERTY()
	int32 Y;

	//变量数据的初始化
	FMyTest() : X(0), Y(0) {}
	
	FMyTest(const int32& X, const int32& Y) : X(X), Y(Y) {}

	FMyTest(const FMyTest& MyTest) :X(MyTest.X), Y(MyTest.Y) {}

};

UCLASS()
class PROJECT_API ATestActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	int32 MyNumber = 0;

	UFUNCTION(BlueprintCallable)
	void Test_1(int32 Number);

	UFUNCTION(BlueprintCallable)
	void Test_2(const int32 Number);
};
