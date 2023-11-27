// Fill out your copyright notice in the Description page of Project Settings.


#include "ChangeLightIntensityComponent.h"

#include "Components/LightComponent.h"

void UChangeLightIntensityComponent::BeginPlay()
{
	Light = GetOwner()->GetComponentByClass<ULightComponent>();
	Super::BeginPlay();
}

bool UChangeLightIntensityComponent::Validate(const FString& Intent, const TMap<FString, FWitEntity>& Map)
{
	if (!Super::Validate(Intent, Map))
		return false;

	if (!Intent.Equals(ChangeIntensityIntent))
		return false;

	return Map.Contains(IntensityEntity);
}

void UChangeLightIntensityComponent::Execute(const FString& Intent, const TMap<FString, FWitEntity>& Map)
{
	const FString& IntensityString = Map[IntensityEntity].Value;
	const int32 Intensity = FCString::Atoi(*IntensityString);
	Light->SetIntensity(Intensity);
}
