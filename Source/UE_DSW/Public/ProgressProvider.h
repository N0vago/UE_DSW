// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "ProgressProvider.generated.h"

/**
 * 
 */
UCLASS()
class UE_DSW_API UProgressProvider : public USaveGame
{
	GENERATED_BODY()
public:
	UProgressProvider();

	UPROPERTY(VisibleAnywhere, Category = Basic)
	TArray<FLinearColor> AvailableColors;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	TArray<FString> UnlockedLevels;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	FString SaveSlotName;
};
