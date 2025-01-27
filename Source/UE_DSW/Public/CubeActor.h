// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ColorHandler.h"
#include "GameFramework/Actor.h"
#include "CubeActor.generated.h"

class UColorHandler;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCubeHit, ACubeActor*, CubeActor);
UCLASS()
class UE_DSW_API ACubeActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACubeActor();

	UColorHandler* GetColorHandler() const { return ColorComponent; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	FOnCubeHit OnCubeHit;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
private:
	virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

	UPROPERTY()
	UColorHandler* ColorComponent;
};
