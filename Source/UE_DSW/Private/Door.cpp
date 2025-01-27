// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"

#include "CubeActor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ADoor::StartCubeColorizeSequence()
{
	for(int i = 0; i < Cubes.Num(); i++)
	{
		Cubes[i]->GetColorHandler()->HiddenColors.Empty();
		Cubes[i]->GetColorHandler()->HitedColors.Empty();
	}
	
	CurrentIlluminationIndex = 0;

	CubeIndex = 0;
	
	IgnitedCubes.Empty();

	HitedCubes.Empty();

	
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ADoor::ChangeCubeColor, DelayBetweenColors, true);
}

bool ADoor::CheckAttempt()
{
	if (IgnitedCubes.Num() != HitedCubes.Num())
	{
		UE_LOG(LogTemp, Error, TEXT("❌ Количество кубов не совпадает! Ignited: %d, Hited: %d"), IgnitedCubes.Num(), HitedCubes.Num());
		return false;
	}

	for (int i = 0; i < IgnitedCubes.Num(); i++)
	{
		if (IgnitedCubes[i] != HitedCubes[i])
		{
			UE_LOG(LogTemp, Error, TEXT("❌ Ошибка! Кубы не совпадают: Ожидалось: %s, Получено: %s"), 
				   *IgnitedCubes[i]->GetName(), 
				   *HitedCubes[i]->GetName());
			return false;
		}

		if (!AreColorsEqual(IgnitedCubes[i]->GetColorHandler()->HiddenColors, HitedCubes[i]->GetColorHandler()->HitedColors, 0.001f))
		{
			UE_LOG(LogTemp, Error, TEXT("❌ Ошибка в `AreColorsEqual()`!"));
			return false;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("✅ Успех! Все кубы и цвета совпадают."));
	return true;
}
bool ADoor::AreColorsEqual(const TArray<FLinearColor>& A, const TArray<FLinearColor>&B, float Tolerance = 0.01f)
{
	if(A.Num() != B.Num())
	{
		return false;
	}
	
	for(int i = 0; i < A.Num(); i++)
	{
		float DeltaR = FMath::Abs(A[i].R - B[i].R);
		float DeltaG = FMath::Abs(A[i].G - B[i].G);
		float DeltaB = FMath::Abs(A[i].B - B[i].B);
		float DeltaA = FMath::Abs(A[i].A - B[i].A);

		bool Result = DeltaR <= Tolerance &&
					  DeltaG <= Tolerance &&
					  DeltaB <= Tolerance &&
					  DeltaA <= Tolerance;

		UE_LOG(LogTemp, Warning, TEXT("A[%d]: %s"), i, *A[i].ToString());
		UE_LOG(LogTemp, Warning, TEXT("B[%d]: %s"), i, *B[i].ToString());
		UE_LOG(LogTemp, Warning, TEXT("🔍 Разница: R(%.6f) G(%.6f) B(%.6f) A(%.6f) | Допуск: %.6f"), 
			   DeltaR, DeltaG, DeltaB, DeltaA, Tolerance);
		if(!Result)
		{
			return false;
		}
	}
	return true;
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	//get ColorHandler components from the owner
	this->Cubes.Empty();
	TArray<UColorHandler*> ColorHandlers;
	GetComponents(ColorHandlers, true);
	for (int i = 0; i < ColorHandlers.Num(); i++)
	{
		ACubeActor* Cube = Cast<ACubeActor>(ColorHandlers[i]->GetOwner());
		if (Cube)
		{
			Cubes.Add(Cube);
			UE_LOG(LogTemp, Warning, TEXT("Добавлен CubeActor: %s"), *Cube->GetName());
			Cube->OnCubeHit.AddDynamic(this, &ADoor::PopulateCubeSet);
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Cubes count: %d"), Cubes.Num());

}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADoor::PopulateCubeSet(ACubeActor* Cube)
{
	UE_LOG(LogTemp, Warning, TEXT("PopulateCubeSet %s"), *Cube->GetName());
	HitedCubes.Add(Cube);
}

void ADoor::ChangeCubeColor()
{
	Cubes[CubeIndex]->GetColorHandler()->SetBaseColor();
	
	CubeIndex = FMath::RandRange(0, Cubes.Num() - 1);
	
	if (CurrentIlluminationIndex >= IlluminationCount)
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		OnSequenceEnd.Broadcast();
		return;
	}

	FLinearColor color = AvailableColors[FMath::RandRange(0, AvailableColors.Num() - 1)];
	
	Cubes[CubeIndex]->GetColorHandler()->SetColor(color);

	IgnitedCubes.Add(Cubes[CubeIndex]);

	UE_LOG(LogTemp, Warning, TEXT("ChangeCubeColor %s with color %s"), *Cubes[CubeIndex]->GetName(), *color.ToString());
	CurrentIlluminationIndex++;
}

