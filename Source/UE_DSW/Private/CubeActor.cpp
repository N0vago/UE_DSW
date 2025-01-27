// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeActor.h"

#include "ColorHandler.h"
#include "UE_DSW/Projectile.h"

// Sets default values
ACubeActor::ACubeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	

}

// Called when the game starts or when spawned
void ACubeActor::BeginPlay()
{
	Super::BeginPlay();
	ColorComponent = FindComponentByClass<UColorHandler>();
}

// Called every frame
void ACubeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACubeActor::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved,
	FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	//check if Other of type UE_DSWProjectile
	if(Other && Cast<AProjectile>(Other))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Projectile hit!"));
		AProjectile* Projectile = Cast<AProjectile>(Other);
		ColorComponent->HitedColors.Add(Projectile->GetProjectileColor());
		OnCubeHit.Broadcast(this);
	}
	
}

