#include "ChangeColorComponent.h"

#include "DemoVoiceExperience.h"
#include "Chaos/SpatialAccelerationCollection.h"

UChangeColorComponent::UChangeColorComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


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

FString UChangeColorComponent::GetObjectName() const
{
	return FString();
}

bool UChangeColorComponent::ValidateEntities(const FString& Intent, const TMap<FString, FWitEntity>& Map)
{
	if (!Map.Contains(ObjectEntity))
		return false;

	const FString ObjName = Map[ObjectEntity].Value;

	if (!ObjName.Equals(GetObjectName(), ESearchCase::IgnoreCase))
		return false;

	if (Intent == ChangeColorIntent && !Map.Contains(ColorEntity))
		return false;

	const FString ColorName = Map[ColorEntity].Value;
	return Experience->IsValidColor(ColorName);
}

bool UChangeColorComponent::ValidateIntent(const FString& Name)
{
	return Name == ChangeColorIntent || Name == ChangeOpacityIntent || Name == ResetColorIntent;
}

void UChangeColorComponent::SetColor(const FColor& Color)
{
}

void UChangeColorComponent::SetOpacity(const float& Value)
{
}

void UChangeColorComponent::ChangeColor(const FString& ColorName)
{
	SetColor(Experience->GetColorByName(ColorName));
}

void UChangeColorComponent::Execute(const FString& Intent, const TMap<FString, FWitEntity>& Map)
{
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, "Executing...");
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, Intent);
	if (Intent.Equals(ChangeColorIntent))
		ChangeColor(Map[ColorEntity].Value);
	else if (Intent.Equals(ResetColorIntent))
		ResetColor();
	else if (Intent.Equals(ChangeOpacityIntent))
		ChangeOpacity(Map[OpacityEntity].Value);
}

void UChangeColorComponent::ResetColor()
{
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, TEXT("reset color"));
	SetColor(DefaultColor);
}

void UChangeColorComponent::ChangeOpacity(const FString& PercentageText)
{
	const int32 Percentage = FCString::Atoi(*PercentageText);
	const float Value = Percentage / 100.f;
	SetOpacity(Value);
}
