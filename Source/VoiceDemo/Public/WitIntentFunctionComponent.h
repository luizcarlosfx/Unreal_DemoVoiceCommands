// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Wit/Request/WitResponse.h"
#include "WitIntentFunctionComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class VOICEDEMO_API UWitIntentFunctionComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	float ConfidenceLevel = 0.5f;

	UPROPERTY()
	class ADemoVoiceExperience* Experience;
	virtual bool ValidateEntities(const FString& Intent, const TMap<FString, FWitEntity>& Map);

public:
	virtual void BeginPlay() override;
	virtual bool ValidateIntent(const FString& Name);
	bool TryExecute(const FWitResponse& Response);

private:
	virtual void Execute(const FString& Intent, const TMap<FString, FWitEntity>& Map);
};
