// 2023 Copyright Labverso, Brazil. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UserWidgetBase.h"
#include "AnimationWidgetBase.generated.h"

/**
* Base class that manages widget animations.
* Will deal with the query of the animation by it's name and also
* the start and stop of the widget's animations clips.
*/
UCLASS()
class WIDGETMODULE_API UAnimationWidgetBase : public UUserWidgetBase
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	/**
	* Tries to get the widget's animation by it's name on the editor.
	* 
	* @param AnimationName The animation name
	* @param OutAnimation The animation found (if found)
	* 
	* @return True if could find the animation
	*/
	UFUNCTION(BlueprintCallable, Category = "Widget")
	virtual bool TryGetAnimationByName(FName AnimationName,
		UWidgetAnimation*& OutAnimation);

	/**
	* Play the widget's animation by it's name
	* 
	* @param AnimationName The animation name to play
	* @param StartAtTime The animation's start time
	* @param NumLoopsToPlay The number of loops to play the animation
	* @param PlayMode The animation's play mode
	* @param PlaybackSpeed The animation's playback speed
	* 
	* @return True if could play the animation
	*/
	UFUNCTION(BlueprintCallable, Category = "Widget")
	virtual bool PlayAnimationByName(FName AnimationName, float StartAtTime,
		int32 NumLoopsToPlay, EUMGSequencePlayMode::Type PlayMode,
		float PlaybackSpeed = 1.0f);

	/**
	* Play the widget's animation by it's name and bind a event when the
	* animation finishes.
	* 
	* @param AnimationName The animation name
	* @param OnFinished The dynamic event to bind
	*/
	UFUNCTION(BlueprintCallable, Category = "Widget")
	virtual void PlayAnimationByNameAndBindFinished(FName AnimationName,
		FWidgetAnimationDynamicEvent OnFinished);

	/**
	* Stop a widget's animation by it's name and unbinds all finished events
	* that were bind on the widget's animation.
	* 
	* @param AnimationName The animation name
	*/
	UFUNCTION(BlueprintCallable, Category = "Widget")
	virtual void StopAnimationByNameAndUnbindFinished(FName AnimationName);

protected:
	/** 
	* Fills the animations map by getting all the widget's animations 
	* that were defined on the editor.
	*/
	UFUNCTION(BlueprintCallable, Category = "Widget")
	void FillAnimationsMap();

protected:
	/** 
	* The map with the widget's animations.
	* As key we have the animation's property name.
	* As value we have a reference to the widget's animation.
	*/
	TMap<FName, TWeakObjectPtr<UWidgetAnimation>> AnimationsMap;
};
