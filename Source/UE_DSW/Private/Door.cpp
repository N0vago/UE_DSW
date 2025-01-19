// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	//get ColorHandler components from the owner
	TArray<UActorComponent*> Components = GetOwner()->GetComponentsByInterface(UColorHandler::StaticClass());
	for (auto Component : Components)
	{
		UE_LOG(LogTemp, Warning, TEXT("ADoor: %s"), *Component->GetName());
	}
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

