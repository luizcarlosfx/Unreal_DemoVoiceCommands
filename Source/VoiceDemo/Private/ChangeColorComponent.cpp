#include "ChangeColorComponent.h"

#include "..\Public\VoiceCommandManager.h"


// Called when the game starts
void UChangeColorComponent::BeginPlay()
{
	Super::BeginPlay();
	DefaultColor = GetCurrentColor();
}

FColor UChangeColorComponent::GetCurrentColor() const
{
	return FColor::Red;
}

bool UChangeColorComponent::Validate(const FString& Intent, const TMap<FString, FWitEntity>& Map)
{
	if (!Super::Validate(Intent, Map))
		return false;

	if (Intent == ChangeColorIntent)
	{
		if (!Map.Contains(ColorEntity))
			return false;

		const FString ColorName = Map[ColorEntity].Value;
		return Manager->IsValidColor(ColorName);
	}

	if (Intent == ChangeOpacityIntent)
		return Map.Contains(OpacityEntity);

	return Intent == ResetColorIntent;
}

void UChangeColorComponent::SetColor(const FColor& Color)
{
}

void UChangeColorComponent::SetOpacity(const float& Value)
{
}

void UChangeColorComponent::ChangeColor(const FString& ColorName)
{
	SetColor(Manager->GetColorByName(ColorName));
}

void UChangeColorComponent::Execute(const FString& Intent, const TMap<FString, FWitEntity>& Map)
{
	if (Intent.Equals(ChangeColorIntent))
		ChangeColor(Map[ColorEntity].Value);
	else if (Intent.Equals(ResetColorIntent))
		ResetColor();
	else if (Intent.Equals(ChangeOpacityIntent))
		ChangeOpacity(Map[OpacityEntity].Value);
}

void UChangeColorComponent::ResetColor()
{
	SetColor(DefaultColor);
}

void UChangeColorComponent::ChangeOpacity(const FString& PercentageText)
{
	const int32 Percentage = FCString::Atoi(*PercentageText);
	const float Value = Percentage / 100.f;
	SetOpacity(Value);
}
