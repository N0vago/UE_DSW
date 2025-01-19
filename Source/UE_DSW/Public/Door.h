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
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	TArray<UColorHandler*> ColorHandlers;

	
};
