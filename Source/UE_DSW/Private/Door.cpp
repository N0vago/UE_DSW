// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ADoor::StartCubeColorizeSequence()
{
	CurrentIlluminationIndex = 0;

	ColorHandlerMap.Empty();
	
	// Запускаем таймер для изменения цвета кубов
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ADoor::ChangeCubeColor, DelayBetweenColors, true);
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	//get ColorHandler components from the owner
	this->ColorHandlers.Empty();
	GetComponents<UColorHandler>(this->ColorHandlers, true);

	StartCubeColorizeSequence();
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADoor::ChangeCubeColor()
{
	ColorHandlers[CubeIndex]->SetBaseColor()();
	
	if (CurrentIlluminationIndex >= IlluminationCount)
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		return;
	}

	FLinearColor color = AvailableColors[FMath::RandRange(0, AvailableColors.Num() - 1)];

	CubeIndex = FMath::RandRange(0, ColorHandlers.Num() - 1);
	
	ColorHandlers[CubeIndex]->SetColor(color);

	ColorHandlerMap.Add(CurrentIlluminationIndex + 1, ColorHandlers[CurrentIlluminationIndex]);

	CurrentIlluminationIndex++;
}

