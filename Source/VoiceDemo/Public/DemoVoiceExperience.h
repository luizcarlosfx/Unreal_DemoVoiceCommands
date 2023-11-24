// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Voice/Experience/VoiceExperience.h"
#include "DemoVoiceExperience.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class VOICEDEMO_API ADemoVoiceExperience : public AVoiceExperience
{
	GENERATED_BODY()

public:

	ADemoVoiceExperience();

	/**
	 * The wit voice service
	 */
	UPROPERTY()
	class UWitVoiceService* WitVoiceService;
	
	/**
	 * The platform voice service
	 */
	UPROPERTY()
	class UPlatformVoiceService* PlatformVoiceService;

	UFUNCTION(BlueprintCallable)
	bool TryActivateVoiceInput();
	UFUNCTION(BlueprintCallable)
	bool TryDeactivateVoiceInput();
	
protected:
	UFUNCTION()
	void OnTranscriptionFinished(const FString& Transcription);
	UFUNCTION()
	void OnWitResponse(const bool bIsSuccessful, const FWitResponse& Response);
	virtual void BeginPlay() override;
};
