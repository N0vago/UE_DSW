// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ColorHandler.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

UCLASS()
class UE_DSW_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:
	ADoor();

	/** Delay between color changes */
	UPROPERTY(EditInstanceOnly, Category = "Color", meta = (ToolTip = "Delay between color changes"))
	float DelayBetweenColors = 0.5f;

	/** Number of cubes to illuminate */
	UPROPERTY(EditInstanceOnly, Category = "Color", meta = (ToolTip = "Number of cubes to illuminate"))
	int IlluminationCount = 0;

	/** Available colors for cubes */
	UPROPERTY(EditInstanceOnly, Category = "Color", meta = (ToolTip = "Available colors for cubes"))
	TArray<FLinearColor> AvailableColors;
	
	void StartCubeColorizeSequence();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY()
	TMap<int, UColorHandler*> ColorHandlerMap;

	UPROPERTY()
	TArray<UColorHandler*> ColorHandlers;
	
	int CurrentIlluminationIndex;

	int CubeIndex;
	
	FTimerHandle TimerHandle;
	
	void ChangeCubeColor();
};
