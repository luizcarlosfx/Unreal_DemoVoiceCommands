// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WitIntentFunctionComponent.h"
#include "Voice/Experience/VoiceExperience.h"
#include "VoiceCommandManager.generated.h"

UCLASS(Blueprintable)
class VOICEDEMO_API AVoiceCommandManager : public AVoiceExperience
{
	GENERATED_BODY()

public:
	AVoiceCommandManager();
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

	UPROPERTY()
	TArray<UWitIntentFunctionComponent*> IntentFunctions;

	UFUNCTION(BlueprintCallable)
	bool TryActivateVoiceInput();
	UFUNCTION(BlueprintCallable)
	bool TryDeactivateVoiceInput();
	void RegisterFunction(UWitIntentFunctionComponent* Function);

	UPROPERTY(EditAnywhere)
	TMap<FString, FString> ColorMap;

	bool IsValidColor(const FString& ColorName) const;
	FColor GetColorByName(const FString& ColorName) const;

protected:
	UFUNCTION()
	void OnWitResponse(const bool bIsSuccessful, const FWitResponse& Response);
	virtual void BeginPlay() override;
	virtual void Destroyed() override;

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, DisplayName="Get VoiceCommands Instance")
	static AVoiceCommandManager* GetInstance();

private:
	inline static AVoiceCommandManager* Instance = nullptr;
};
