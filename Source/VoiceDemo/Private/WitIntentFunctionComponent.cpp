// Fill out your copyright notice in the Description page of Project Settings.


#include "WitIntentFunctionComponent.h"

#include "DemoVoiceExperience.h"

bool UWitIntentFunctionComponent::ValidateEntities(const FString& Intent, const TMap<FString, FWitEntity>& Map)
{
	return true;
}

void UWitIntentFunctionComponent::BeginPlay()
{
	Super::BeginPlay();
	Experience = Cast<ADemoVoiceExperience>(GetOwner());
}

bool UWitIntentFunctionComponent::ValidateIntent(const FString& Name)
{
	return false;
}

bool UWitIntentFunctionComponent::TryExecute(const FWitResponse& Response)
{
	TArray<FWitIntent> Intents = Response.Intents;

	if (Intents.Num() < 0)
		return false;

	const FWitIntent& Intent = Intents[0];
	const FString& IntentName = Intent.Name;
	
	if (Intent.Confidence < ConfidenceLevel || !ValidateIntent(IntentName))
		return false;

	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, TEXT("Intent Validated"));

	const TMap<FString, FWitEntity>& Entities = Response.Entities;

	// for (const TTuple<FString, FWitEntity>& Tuple : Entities)
	// {
	// 	if (Tuple.Value.Confidence < ConfidenceLevel)
	// 		return false;
	// }

	if (ValidateEntities(IntentName, Entities))
	{
		Execute(IntentName, Entities);
		return true;
	}

	return false;
}

void UWitIntentFunctionComponent::Execute(const FString& Intent, const TMap<FString, FWitEntity>& Map)
{
}
