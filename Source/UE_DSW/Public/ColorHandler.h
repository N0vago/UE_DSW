// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ColorHandler.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE_DSW_API UColorHandler : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UColorHandler();

	UPROPERTY(EditAnywhere, Category = "Color")
	FLinearColor BaseColor;
	
	void SetColor(const FLinearColor& Color);

	void SetBaseColor();

	FLinearColor GetHiddenColor() const { return HiddenColor; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY()
	UMaterialInstanceDynamic* DynMaterial;

	UPROPERTY()
	UStaticMeshComponent* MeshComponent;

	UPROPERTY()
	FLinearColor HiddenColor;
};
