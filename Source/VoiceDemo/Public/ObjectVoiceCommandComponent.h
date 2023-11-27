// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VoiceCommandComponent.h"
#include "ObjectVoiceCommandComponent.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class VOICEDEMO_API UObjectVoiceCommandComponent : public UVoiceCommandComponent
{
	GENERATED_BODY()

public:
	virtual bool Validate(const FString& Intent, const TMap<FString, FWitEntity>& Map) override;

protected:
	UObjectVoiceCommandComponent();

private:
	UPROPERTY(EditAnywhere)
	FString TargetObjectName;

	UPROPERTY(EditAnywhere)
	FString ObjectEntity = "object:object";
};
