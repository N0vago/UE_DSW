// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Blueprint/UserWidget.h"
#include "ColorSelector.generated.h"

UCLASS()
class UE_DSW_API UColorSelector : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta = (BindWidget))
	class UImage* Image1;

	UPROPERTY(meta = (BindWidget))
	class UImage* Image2;

	UPROPERTY(meta = (BindWidget))
	class UImage* Image3;

	UFUNCTION(BlueprintCallable)
	void AddAvailableColor(const FLinearColor& Color) { AvailableColors.Add(Color); }
	
	FLinearColor GetSelectedColor() const { return SelectedColor; }
	
	void UpdateImageSelection();

	void NavigateUI(const float& Value);

protected:
	virtual void NativeConstruct() override;

private:
	TArray<FLinearColor> GetColors();

	UPROPERTY()
	AGameModeBase* GameMode;

	UPROPERTY(BlueprintReadOnly, Category = "Color", meta = (AllowPrivateAccess = "true"))  
	FLinearColor SelectedColor;

	UPROPERTY()
	TArray<FLinearColor> AvailableColors;
	
	int32 SelectedIndex = 0;
};
