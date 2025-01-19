// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE_DSWPickUpComponent.h"

UUE_DSWPickUpComponent::UUE_DSWPickUpComponent()
{
	// Setup the Sphere Collision
	SphereRadius = 32.f;
}

void UUE_DSWPickUpComponent::BeginPlay()
{
	Super::BeginPlay();

	// Register our Overlap Event
	OnComponentBeginOverlap.AddDynamic(this, &UUE_DSWPickUpComponent::OnSphereBeginOverlap);
}

void UUE_DSWPickUpComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Checking if it is a First Person Character overlapping
	AUE_DSWCharacter* Character = Cast<AUE_DSWCharacter>(OtherActor);
	if(Character != nullptr)
	{
		// Notify that the actor is being picked up
		OnPickUp.Broadcast(Character);

		// Unregister from the Overlap Event so it is no longer triggered
		OnComponentBeginOverlap.RemoveAll(this);
	}
}
