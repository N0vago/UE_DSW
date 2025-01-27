// Fill out your copyright notice in the Description page of Project Settings.


#include "ColorSelector.h"
#include "Components/Image.h"
#include "Kismet/KismetMathLibrary.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "UE_DSW/Structs/GameColors.h"

void UColorSelector::NativeConstruct()
{
	Super::NativeConstruct();

	TArray<UImage*> Images = {Image1, Image2, Image3};
	AvailableColors = GetColors();
	for(int32 i = 0; i < Images.Num(); i++)
	{
		if (i < AvailableColors.Num())
		{
			Images[i]->SetColorAndOpacity(AvailableColors[i]);
		}
	}
	Image2->SetRenderScale(FVector2D(1.5f, 1.5f));
	UpdateImageSelection();
}


void UColorSelector::UpdateImageSelection()
{
	TArray<UImage*> Images = {Image1, Image2, Image3};
	
	for (int32 i = 0; i < Images.Num(); i++)
	{
		Images[i]->SetColorAndOpacity(AvailableColors[(i + SelectedIndex) % AvailableColors.Num()]);
	}
	SelectedColor = Image2->GetColorAndOpacity();
}

void UColorSelector::NavigateUI(const float& Value)
{
	if (Value > 0)
	{
		SelectedIndex = (SelectedIndex + 1) % AvailableColors.Num();
	}
	else if (Value < 0)
	{
		SelectedIndex = (SelectedIndex - 1 + AvailableColors.Num()) % AvailableColors.Num();
	}
	UpdateImageSelection();
}


TArray<FLinearColor> UColorSelector::GetColors()
{
	UDataTable* ColorTable = LoadObject<UDataTable>(nullptr, TEXT("DataTable'/Game/GameContent/Blueprints/DT_ColorData.DT_ColorData'"));
	if (ColorTable)
	{
		FGameColors* ColorRow = ColorTable->FindRow<FGameColors>(FName("Level"), FString(""));
		if (ColorRow)
		{
			return ColorRow->Colors;
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("ColorTable is nullptr"));
	return TArray<FLinearColor>();
}
