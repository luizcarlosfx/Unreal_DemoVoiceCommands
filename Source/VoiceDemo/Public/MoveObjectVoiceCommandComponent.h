// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObjectVoiceCommandComponent.h"
#include "MoveObjectVoiceCommandComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=(VoiceCommands), meta=(BlueprintSpawnableComponent))
class VOICEDEMO_API UMoveObjectVoiceCommandComponent : public UObjectVoiceCommandComponent
{
	GENERATED_BODY()

public:
	virtual bool Validate(const FString& Intent, const TMap<FString, FWitEntity>& Map) override;
	virtual void Execute(const FString& Intent, const TMap<FString, FWitEntity>& Map) override;
private:
	UPROPERTY(EditAnywhere)
	FString MoveObjectIntent = "move_object";

	UPROPERTY(EditAnywhere)
	FString DirectionEntity = "direction:direction";

	UPROPERTY(EditAnywhere)
	float TargetMovementLength = 100;

	void MoveOwnerToLocation(const FVector& Location) const;
};
