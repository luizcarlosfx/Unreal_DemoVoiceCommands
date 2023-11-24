// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoVoiceExperience.h"

#include "WitIntentFunctionComponent.h"
#include "Voice/Platform/PlatformVoiceService.h"
#include "Wit/Voice/WitVoiceService.h"

ADemoVoiceExperience::ADemoVoiceExperience()
	: Super()
{
	WitVoiceService = CreateDefaultSubobject<UWitVoiceService>(TEXT("WitVoiceService"));
	PlatformVoiceService = CreateDefaultSubobject<UPlatformVoiceService>(TEXT("PlatformVoiceService"));

	VoiceService = WitVoiceService;
}

void ADemoVoiceExperience::OnTranscriptionFinished(const FString& Transcription)
{
	// GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, Transcription);
}

void ADemoVoiceExperience::OnWitResponse(const bool bIsSuccessful, const FWitResponse& Response)
{
	if (!bIsSuccessful)
		return;

	const TArray<FWitIntent>& Intents = Response.Intents;

	if (Intents.Num() == 0)
		return;

	for (UWitIntentFunctionComponent* IntentFunction : IntentFunctions)
	{
		if (IntentFunction->TryExecute(Response))
			break;
	}

	FString DebugMessage = Response.Intents[0].Name + "(";

	bool bIsFirst = true;

	for (TTuple<FString, FWitEntity> Tuple : Response.Entities)
	{
		if (!bIsFirst)
			DebugMessage.Append(", ");
		else
			bIsFirst = false;

		DebugMessage.Append(Tuple.Value.Value + ":" + Tuple.Value.Role);
	}

	DebugMessage.Append(")");

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

	GetComponents<UWitIntentFunctionComponent>(IntentFunctions);

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

bool ADemoVoiceExperience::IsValidColor(const FString& ColorName) const
{
	return ColorMap.Contains(ColorName);
}

FColor ADemoVoiceExperience::GetColorByName(const FString& ColorName) const
{
	if (!ColorMap.Contains(ColorName))
		return FColor::White;

	const FString ColorHex = ColorMap[ColorName];
	return FColor::FromHex(ColorHex);
}
