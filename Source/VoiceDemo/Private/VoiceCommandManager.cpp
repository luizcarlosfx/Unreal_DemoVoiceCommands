// Fill out your copyright notice in the Description page of Project Settings.


#include "..\Public\VoiceCommandManager.h"

#include "VoiceCommandComponent.h"
#include "Voice/Platform/PlatformVoiceService.h"
#include "Wit/Voice/WitVoiceService.h"

AVoiceCommandManager::AVoiceCommandManager()
	: Super()
{
	WitVoiceService = CreateDefaultSubobject<UWitVoiceService>(TEXT("WitVoiceService"));
	PlatformVoiceService = CreateDefaultSubobject<UPlatformVoiceService>(TEXT("PlatformVoiceService"));

	VoiceService = WitVoiceService;
	Instance = this;
}

void AVoiceCommandManager::OnWitResponse(const bool bIsSuccessful, const FWitResponse& Response)
{
	if (!bIsSuccessful)
		return;

	const TArray<FWitIntent>& Intents = Response.Intents;

	if (Intents.Num() == 0)
		return;

	for (UVoiceCommandComponent* IntentFunction : IntentFunctions)
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
void AVoiceCommandManager::BeginPlay()
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
	VoiceEvents->OnWitResponse.AddDynamic(this, &AVoiceCommandManager::OnWitResponse);
}

void AVoiceCommandManager::Destroyed()
{
	Super::Destroyed();
	Instance = nullptr;
}

AVoiceCommandManager* AVoiceCommandManager::GetInstance()
{
	return Instance;
}

bool AVoiceCommandManager::TryActivateVoiceInput()
{
	if (IsVoiceInputActive() || IsRequestInProgress())
		return false;

	const bool bResult = ActivateVoiceInput();

	if (bResult)
		GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Green, TEXT("Voice Input Activated!"));

	return bResult;
}

bool AVoiceCommandManager::TryDeactivateVoiceInput()
{
	if (IsRequestInProgress() || !IsVoiceInputActive())
		return false;

	const bool bResult = DeactivateVoiceInput();

	if (bResult)
		GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Red, TEXT("Voice Input Deactivated!"));

	return bResult;
}

void AVoiceCommandManager::RegisterCommand(UVoiceCommandComponent* Function)
{
	IntentFunctions.Add(Function);
}

bool AVoiceCommandManager::IsValidColor(const FString& ColorName) const
{
	return ColorMap.Contains(ColorName);
}

FColor AVoiceCommandManager::GetColorByName(const FString& ColorName) const
{
	if (!ColorMap.Contains(ColorName))
		return FColor::White;

	const FString ColorHex = ColorMap[ColorName];
	return FColor::FromHex(ColorHex);
}
