// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObjectVoiceCommandComponent.h"
#include "MoveObjectVoiceCommandComponent.generated.h"

/**
 * 
 */
UCLASS()
class VOICEDEMO_API UMoveObjectVoiceCommandComponent : public UObjectVoiceCommandComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	FString MoveObjectIntent = "move_object";

	UPROPERTY(EditAnywhere)
	FString DirectionEntity = "direction:direction";

	UPROPERTY(EditAnywhere)
	float TargetMovementLength = 100;
};
