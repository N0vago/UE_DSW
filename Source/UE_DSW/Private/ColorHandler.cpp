#include "ColorHandler.h"

UColorHandler::UColorHandler()
{
	PrimaryComponentTick.bCanEverTick = true;

	DynMaterial = nullptr;
	
	MeshComponent = nullptr;
	
}

void UColorHandler::SetColor(const FLinearColor& Color)
{
	if (!MeshComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("UColorHandler: MeshComponent is null!"));
		return;
	}
	
	UMaterialInterface* BaseMaterial = MeshComponent->GetMaterial(0);
	if (BaseMaterial)
	{
		if(DynMaterial == nullptr)
		{
			DynMaterial = UMaterialInstanceDynamic::Create(BaseMaterial, this);
		}
		
		MeshComponent->SetMaterial(0, DynMaterial);
		
		DynMaterial->SetVectorParameterValue("BaseColor", Color);

		HiddenColor = Color;
	}

}

void UColorHandler::SetBaseColor()
{
	if (!MeshComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("UColorHandler: MeshComponent is null!"));
		return;
	}
	
	UMaterialInterface* BaseMaterial = MeshComponent->GetMaterial(0);
	if (BaseMaterial)
	{
		if(DynMaterial == nullptr)
		{
			DynMaterial = UMaterialInstanceDynamic::Create(BaseMaterial, this);
		}
		
		MeshComponent->SetMaterial(0, DynMaterial);
		
		DynMaterial->SetVectorParameterValue("BaseColor", BaseColor);
	}
}

void UColorHandler::BeginPlay()
{
	Super::BeginPlay();

	MeshComponent = GetOwner()->FindComponentByClass<UStaticMeshComponent>();
}

void UColorHandler::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

