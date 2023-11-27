// Fill out your copyright notice in the Description page of Project Settings.


#include "ChangeLightColorComponent.h"

#include "Components/LightComponent.h"
#include "Components/LightComponentBase.h"

void UChangeLightColorComponent::BeginPlay()
{
	Light = GetOwner()->GetComponentByClass<ULightComponent>();
	Super::BeginPlay();
}

FColor UChangeLightColorComponent::GetCurrentColor() const
{
	return Light->LightColor;
}

void UChangeLightColorComponent::SetColor(const FColor& Color)
{
	Light->SetLightFColor(Color);
}
