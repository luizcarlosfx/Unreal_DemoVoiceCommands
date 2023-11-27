// Fill out your copyright notice in the Description page of Project Settings.


#include "ChangeStaticMeshColorComponent.h"

void UChangeStaticMeshColorComponent::BeginPlay()
{
	UStaticMeshComponent* MeshComponent = GetOwner()->FindComponentByClass<UStaticMeshComponent>();
	UMaterialInterface* Interface = MeshComponent->GetMaterial(MaterialIndex);
	Material = UMaterialInstanceDynamic::Create(Interface, nullptr);
	MeshComponent->SetMaterial(MaterialIndex, Material);
	Super::BeginPlay();
}

void UChangeStaticMeshColorComponent::SetColor(const FColor& Color)
{
	Material->SetVectorParameterValue(PropertyName, Color);
	Material->UpdateCachedData();
}

FColor UChangeStaticMeshColorComponent::GetCurrentColor() const
{
	FLinearColor Color;
	Material->GetVectorParameterValue(PropertyName, Color);
	return Color.ToFColor(false);
}

void UChangeStaticMeshColorComponent::SetOpacity(const float& Value)
{
}
