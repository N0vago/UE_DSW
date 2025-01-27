// Copyright Epic Games, Inc. All Rights Reserved.

#include "MainGameMode.h"
#include "PlayerCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMainGameMode::AMainGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}

void AMainGameMode::BeginPlay()
{
	Super::BeginPlay();

	UDataTable* ColorTable = LoadObject<UDataTable>(nullptr, TEXT("DataTable'/Game/DT_ColorTable.DT_ColorTable'"));
	if (ColorTable)
	{
		FName RowName = "Level1";
		uint8* RowData = ColorTable->FindRowUnchecked(RowName);

		if (RowData)
		{
			FArrayProperty* ColorArrayProperty = CastField<FArrayProperty>(ColorTable->GetRowStruct()->FindPropertyByName("Colors"));

			if (ColorArrayProperty)
			{
				FScriptArrayHelper ArrayHelper(ColorArrayProperty, RowData);

				for (int32 i = 0; i < ArrayHelper.Num(); i++)
				{
					FLinearColor* ColorPtr = (FLinearColor*)ArrayHelper.GetRawPtr(i);
					if (ColorPtr)
					{
						UE_LOG(LogTemp, Log, TEXT("Color: R=%.2f, G=%.2f, B=%.2f, A=%.2f"), 
							ColorPtr->R, ColorPtr->G, ColorPtr->B, ColorPtr->A);
					}
				}
			}
		}
	}
}
