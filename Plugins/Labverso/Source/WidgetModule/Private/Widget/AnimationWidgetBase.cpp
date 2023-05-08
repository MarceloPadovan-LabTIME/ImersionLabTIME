// 2023 Copyright Labverso, Brazil. All Rights Reserved.

#include "Widget/AnimationWidgetBase.h"
#include "Animation/WidgetAnimation.h"
#include "WidgetModule/WidgetModuleLogDeclaration.h"

void UAnimationWidgetBase::NativeConstruct()
{
	// Fill the animations map by getting the animations created on editor
	FillAnimationsMap();

	// Call Blueprint Event Construct node
	Super::NativeConstruct();
}

void UAnimationWidgetBase::FillAnimationsMap()
{
	AnimationsMap.Empty();

	// The the class property iterator
	for (TFieldIterator<FObjectProperty> PropIt(GetClass()); PropIt; ++PropIt)
	{
		const FObjectProperty* Prop = *PropIt;

		// If the property is not of type WidgetAnimation
		if (Prop->PropertyClass != UWidgetAnimation::StaticClass())
		{
			continue;
		}

		// The the property as widget animation
		UWidgetAnimation* WidgetAnim = Cast<UWidgetAnimation>
			(Prop->GetObjectPropertyValue_InContainer(this));

		if (WidgetAnim == nullptr || WidgetAnim->MovieScene == nullptr)
		{
			continue;
		}

		// Get the animation's name
		const FName AnimName = WidgetAnim->MovieScene->GetFName();

		// Add on the animations map
		AnimationsMap.Add(AnimName, WidgetAnim);
	}
}

bool UAnimationWidgetBase::TryGetAnimationByName(FName AnimationName, 
	UWidgetAnimation*& OutAnimation)
{
	// Check if the animation's name is valid
	if (AnimationName.IsNone())
	{
		UE_LOG(LogWidgetModule, Error, TEXT("Could not get animation as the\
			animation's name to find is empty"));
		return false;
	}

	// Try to find the animation in the AnimationsMap
	if (const auto& WidgetAnim = AnimationsMap.Find(AnimationName))
	{
		// If the animation is valid, assign it to OutAnimation pointer
		OutAnimation = WidgetAnim->IsValid()
			            ? WidgetAnim->Get()
			            : nullptr;
		return true;
	}

	return false;
}

bool UAnimationWidgetBase::PlayAnimationByName(FName AnimationName,
	float StartAtTime,  int32 NumLoopsToPlay, 
	EUMGSequencePlayMode::Type PlayMode, float PlaybackSpeed)
{
	// Try to find the animation
	UWidgetAnimation* WidgetAnim = nullptr;
	if (!TryGetAnimationByName(AnimationName, WidgetAnim))
	{
		return false;
	}

	// Play animation
	PlayAnimation(WidgetAnim, StartAtTime, NumLoopsToPlay, PlayMode, 
		PlaybackSpeed);
	return true;
}

void UAnimationWidgetBase::PlayAnimationByNameAndBindFinished
	(FName AnimationName, FWidgetAnimationDynamicEvent OnFinished)
{
	// Try to find the animation, if any
	UWidgetAnimation* WidgetAnim = nullptr;
	if (!TryGetAnimationByName(AnimationName, WidgetAnim))
	{
		return;
	}

	// Bind dynamic event if it is bound and play animation
	OnFinished.IsBound() ?
		BindToAnimationFinished(WidgetAnim, OnFinished) :
		void();

	PlayAnimation(WidgetAnim);
}

void UAnimationWidgetBase::StopAnimationByNameAndUnbindFinished
	(FName AnimationName)
{
	// Get animation by name, if any
	UWidgetAnimation* WidgetAnim = nullptr;
	if (!TryGetAnimationByName(AnimationName, WidgetAnim))
	{
		return;
	}

	// Unbind all dynamic events and stop animation
	UnbindAllFromAnimationFinished(WidgetAnim);
	StopAnimation(WidgetAnim);
}
