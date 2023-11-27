// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChangeColorComponent.h"
#include "ChangeLightColorComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=(VoiceCommands), meta=(BlueprintSpawnableComponent))
class VOICEDEMO_API UChangeLightColorComponent : public UChangeColorComponent
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual FColor GetCurrentColor() const override;
	virtual void SetColor(const FColor& Color) override;

private:
	UPROPERTY()
	ULightComponent* Light;
};
