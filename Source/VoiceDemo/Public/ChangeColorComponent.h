// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObjectVoiceCommandComponent.h"
#include "VoiceCommandComponent.h"
#include "Components/ActorComponent.h"
#include "ChangeColorComponent.generated.h"

UCLASS(ClassGroup=(Custom), Abstract)
class VOICEDEMO_API UChangeColorComponent : public UObjectVoiceCommandComponent
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual FColor GetCurrentColor() const;
	virtual bool Validate(const FString& Intent, const TMap<FString, FWitEntity>& Map) override;
	virtual void SetColor(const FColor& Color);
	virtual void SetOpacity(const float& Value);
	void ChangeColor(const FString& ColorName);
	void ResetColor();
	void ChangeOpacity(const FString& PercentageText);
	virtual void Execute(const FString& Intent, const TMap<FString, FWitEntity>& Map) override;
	
	UPROPERTY(EditAnywhere)
	FString ChangeColorIntent = "change_object_color";

	UPROPERTY(EditAnywhere)
	FString ResetColorIntent = "reset_object_color";

	UPROPERTY(EditAnywhere)
	FString ChangeOpacityIntent = "change_object_opacity";

	UPROPERTY(EditAnywhere)
	FString OpacityEntity = "wit$number:percentage";

	UPROPERTY(EditAnywhere)
	FString ColorEntity = "color:color";

private:
	FColor DefaultColor;
};
