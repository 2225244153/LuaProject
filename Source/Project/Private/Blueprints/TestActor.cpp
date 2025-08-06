// Fill out your copyright notice in the Description page of Project Settings.


#include "Blueprints/TestActor.h"

// Sets default values
ATestActor::ATestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATestActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATestActor::Test_1(int32 Number)
{
	Number++;
}

void ATestActor::Test_2(const int32  Number)
{
	UE_LOG(LogTemp, Warning,TEXT(" Number = %d"), Number)
}

