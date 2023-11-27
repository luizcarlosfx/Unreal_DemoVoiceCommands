// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectVoiceCommandComponent.h"

bool UObjectVoiceCommandComponent::Validate(const FString& Intent, const TMap<FString, FWitEntity>& Map)
{
	if (!Map.Contains(ObjectEntity))
		return false;

	return Map[ObjectEntity].Value.Equals(TargetObjectName, ESearchCase::IgnoreCase);
}

UObjectVoiceCommandComponent::UObjectVoiceCommandComponent()
{
	if (const AActor* Owner = GetOwner())
		TargetObjectName = Owner->GetActorLabel();
}
