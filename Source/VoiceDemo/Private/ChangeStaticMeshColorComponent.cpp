// Fill out your copyright notice in the Description page of Project Settings.


#include "ChangeStaticMeshColorComponent.h"

#include "Engine/StaticMeshActor.h"


void UChangeStaticMeshColorComponent::BeginPlay()
{
	UStaticMeshComponent* MeshComponent = MeshActor->GetStaticMeshComponent();
	UMaterialInterface* Interface = MeshComponent->GetMaterial(MaterialIndex);
	Material = UMaterialInstanceDynamic::Create(Interface, nullptr);
	MeshComponent->SetMaterial(MaterialIndex, Material);
	Super::BeginPlay();
	// SetColor(FColor::Red);
}

FString UChangeStaticMeshColorComponent::GetObjectName() const
{
	return MeshActor->GetName();
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
