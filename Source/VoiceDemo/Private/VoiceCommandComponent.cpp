// Fill out your copyright notice in the Description page of Project Settings.


#include "VoiceCommandComponent.h"

#include "..\Public\VoiceCommandManager.h"

UVoiceCommandComponent::UVoiceCommandComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

bool UVoiceCommandComponent::Validate(const FString& Intent, const TMap<FString, FWitEntity>& Map)
{
	return true;
}

void UVoiceCommandComponent::BeginPlay()
{
	Super::BeginPlay();
	Manager = AVoiceCommandManager::GetInstance();
	Manager->RegisterCommand(this);
}

bool UVoiceCommandComponent::TryExecute(const FWitResponse& Response)
{
	TArray<FWitIntent> Intents = Response.Intents;

	if (Intents.Num() < 0)
		return false;

	const FWitIntent& Intent = Intents[0];
	const FString& IntentName = Intent.Name;
	
	if (Intent.Confidence < ConfidenceLevel)
		return false;

	const TMap<FString, FWitEntity>& Entities = Response.Entities;

	for (const TTuple<FString, FWitEntity>& Tuple : Entities)
	{
		if (Tuple.Value.Confidence < ConfidenceLevel)
			return false;
	}

	if (Validate(IntentName, Entities))
	{
		Execute(IntentName, Entities);
		return true;
	}

	return false;
}

void UVoiceCommandComponent::Execute(const FString& Intent, const TMap<FString, FWitEntity>& Map)
{
}
