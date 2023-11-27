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
	for (TTuple<FString, FWitEntity> Tuple : Map)
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Yellow, Tuple.Key);
	
	if (!Intent.Equals(ChangeIntensityIntent))
		return false;

	if (!Map.Contains(ObjectEntity))
		return false;

	const FString& ObjectName = Map[ObjectEntity].Value;

	if (!ObjectName.Equals(TargetLightName, ESearchCase::IgnoreCase))
		return false;
	
	return Map.Contains(IntensityEntity);
}

void UChangeLightIntensityComponent::Execute(const FString& Intent, const TMap<FString, FWitEntity>& Map)
{
	const FString& IntensityString = Map[IntensityEntity].Value;
	const int32 Intensity = FCString::Atoi(*IntensityString);
	Light->SetIntensity(Intensity);
}
