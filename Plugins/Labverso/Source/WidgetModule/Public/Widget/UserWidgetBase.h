// 2023 Copyright Labverso, Brazil. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserWidgetBase.generated.h"

/** 
* Base class for all widgets that should be managed by the WidgetModule's HUD.
* This class deals with base functionalities of all widgets, such as showing,
* hiding, toggling visibility, getting it's HUD and etc.
*/
UCLASS()
class WIDGETMODULE_API UUserWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
	/** 
	* Shows the widget by setting it's visibility 
	* to the default visibility. 
	*/
	UFUNCTION(BlueprintCallable, Category = "Widget Module")
	virtual void ShowWidget();

	/** Hides the widget by setting it's visibility to Hidden */
	UFUNCTION(BlueprintCallable, Category = "Widget Module")
	virtual void HideWidget();

	/** 
	* Toggles the widget visibility.
	* If visible will hide it and if hidden will set to visible.
	* 
	* @note That this should be overwritten if the widget's default visibility
	* is not "Visible". This may block the player's input on the game as
	* a "Visible" visibility will be hit-testable and may break the interface.
	*/
	UFUNCTION(BlueprintCallable, Category = "Widget Module")
	virtual void ToggleWidgetVisibility();

	/** Destroys the widget */
	UFUNCTION(BlueprintCallable, Category = "Widget Module")
	virtual void DestroyWidget();

	/** Sets the owning HUD */
	UFUNCTION(BlueprintCallable, Category = "Widget Module")
	void SetOwningHUD(class AWidgetModuleHUD* InOwningHUD) 
		{ OwningHUD = InOwningHUD; }

	/** Getter to the owning HUD of this widget */
	UFUNCTION(BlueprintCallable, Category = "Widget Module")
	FORCEINLINE class AWidgetModuleHUD* GetOwningHUD() const 
		{ return OwningHUD; }

	/** Get the owning HUD with the given type */
	template <class T= class AWidgetModuleHUD>
	FORCEINLINE T* GetOwningHUD() const { return Cast<T>(OwningHUD); }

private:
	/** 
	* The default visibility for this widget. 
	* As default (also for UE), every widget is visible but not hit-testable.
	*/
	UPROPERTY(EditDefaultsOnly, Category = "Properties", 
		meta = (AllowPrivateAccess = "true"))
	ESlateVisibility DefaultSlateVisibility = 
		ESlateVisibility::SelfHitTestInvisible;

	/** 
	* The actor that requested the widget's creationg. 
	* I.e, the owning HUD. 
	*/
	UPROPERTY(BlueprintReadOnly, Category = "Properties", 
		meta = (AllowPrivateAccess = "true"))
	class AWidgetModuleHUD* OwningHUD = nullptr;
};
