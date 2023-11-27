// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveObjectVoiceCommandComponent.h"

#include "FCTween.h"
#include "VoiceCommandManager.h"

bool UMoveObjectVoiceCommandComponent::Validate(const FString& Intent, const TMap<FString, FWitEntity>& Map)
{
	if (!Super::Validate(Intent, Map))
		return false;

	if (!Intent.Equals(MoveObjectIntent))
		return false;

	if (!Map.Contains(DirectionEntity))
		return false;

	const FString& Direction = Map[DirectionEntity].Value;
	return Manager->IsValidDirection(Direction);
}

void UMoveObjectVoiceCommandComponent::Execute(const FString& Intent, const TMap<FString, FWitEntity>& Map)
{
	const FString& DirectionName = Map[DirectionEntity].Value;
	const FVector& DirectionVector = Manager->GetDirectionByName(DirectionName);

	const FVector& Start = GetOwner()->GetActorLocation();
	const FVector End = Start + DirectionVector * TargetMovementLength;

	FCTween::Play(Start, End, [&](const FVector& Location) { MoveOwnerToLocation(Location); }, 0.75f, EFCEase::OutCubic);
}

void UMoveObjectVoiceCommandComponent::MoveOwnerToLocation(const FVector& Location) const
{
	GetOwner()->SetActorLocation(Location);
}
