// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WitIntentFunctionComponent.h"
#include "ChangeLightIntensityComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=(VoiceCommands), meta=(BlueprintSpawnableComponent))
class VOICEDEMO_API UChangeLightIntensityComponent : public UWitIntentFunctionComponent
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual bool Validate(const FString& Intent, const TMap<FString, FWitEntity>& Map) override;
	virtual void Execute(const FString& Intent, const TMap<FString, FWitEntity>& Map) override;

private:
	UPROPERTY(EditAnywhere)
	FString IntensityEntity = "wit$number:intensity";

	UPROPERTY(EditAnywhere)
	FString ObjectEntity = "object:object";

	UPROPERTY(EditAnywhere)
	FString ChangeIntensityIntent = "change_light_intensity";

	UPROPERTY(EditAnywhere)
	FString TargetLightName = "light";

	UPROPERTY()
	class ULightComponent* Light;
};
