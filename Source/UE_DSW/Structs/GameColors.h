#pragma once

#include "CoreMinimal.h"
#include "GameColors.generated.h"

USTRUCT(BlueprintType)
struct UE_DSW_API FGameColors : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite ,Category = "Color")
	TArray<FLinearColor> Colors;
	
};
