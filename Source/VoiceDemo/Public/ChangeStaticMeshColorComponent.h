// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChangeColorComponent.h"
#include "ChangeStaticMeshColorComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=(VoiceCommands), meta=(BlueprintSpawnableComponent))
class VOICEDEMO_API UChangeStaticMeshColorComponent : public UChangeColorComponent
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
protected:
	virtual void SetColor(const FColor& Color) override;
	virtual FColor GetCurrentColor() const override;
	virtual void SetOpacity(const float& Value) override;
private:
	UPROPERTY(EditInstanceOnly)
	int MaterialIndex = 0;

	UPROPERTY(EditAnywhere)
	FName PropertyName = "Color";

	UPROPERTY()
	UMaterialInstanceDynamic* Material;
};
