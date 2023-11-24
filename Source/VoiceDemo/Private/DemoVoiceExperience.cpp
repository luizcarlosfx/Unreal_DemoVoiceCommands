// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoVoiceExperience.h"

#include "Voice/Platform/PlatformVoiceService.h"
#include "Wit/Voice/WitVoiceService.h"

/**
 * Sets default values for this actor's properties
 */
ADemoVoiceExperience::ADemoVoiceExperience()
	: Super()
{
	WitVoiceService = CreateDefaultSubobject<UWitVoiceService>(TEXT("WitVoiceService"));
	PlatformVoiceService = CreateDefaultSubobject<UPlatformVoiceService>(TEXT("PlatformVoiceService"));

	VoiceService = WitVoiceService;
}

void ADemoVoiceExperience::OnTranscriptionFinished(const FString& Transcription)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, Transcription);
}

void ADemoVoiceExperience::OnWitResponse(const bool bIsSuccessful, const FWitResponse& Response)
{
	FString DebugMessage;

	TArray<FWitIntent> Intents = Response.Intents;
	
	for (TTuple<FString, FWitEntity> Tuple : Response.Entities)
	{
		DebugMessage.Append(Tuple.Value.Role + ", " + Tuple.Value.Value + "\n");	
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, DebugMessage);
}

/**
 * Called when play starts. Decides which voice service to use
 */
void ADemoVoiceExperience::BeginPlay()
{
	const bool bShouldUsePlatformIntegration = Configuration != nullptr && Configuration->Application.Advanced.bIsPlatformIntegrationEnabled;
	UE_LOG(LogTemp, Display, TEXT("Init VoiceService: bIsPlatformIntegrationEnabled=%s"), bShouldUsePlatformIntegration ? TEXT("true") : TEXT("false"));

	if (bShouldUsePlatformIntegration)
	{
		VoiceService = PlatformVoiceService;
	}
	else
	{
		VoiceService = WitVoiceService;
	}

	Super::BeginPlay();
	VoiceEvents->OnFullTranscription.AddDynamic(this, &ADemoVoiceExperience::OnTranscriptionFinished);
	VoiceEvents->OnWitResponse.AddDynamic(this, &ADemoVoiceExperience::OnWitResponse);
}

bool ADemoVoiceExperience::TryActivateVoiceInput()
{
	if (IsVoiceInputActive() || IsRequestInProgress())
		return false;

	const bool bResult = ActivateVoiceInput();

	if (bResult)
		GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Green, TEXT("Voice Input Activated!"));

	return bResult;
}

bool ADemoVoiceExperience::TryDeactivateVoiceInput()
{
	if (IsRequestInProgress() || !IsVoiceInputActive())
		return false;

	const bool bResult = DeactivateVoiceInput();

	if (bResult)
		GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Red, TEXT("Voice Input Deactivated!"));

	return bResult;
}
