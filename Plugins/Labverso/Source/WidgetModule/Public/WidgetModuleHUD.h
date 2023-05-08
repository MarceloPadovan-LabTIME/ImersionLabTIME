// 2023 Copyright Labverso, Brazil. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Widget/UserWidgetBase.h"
#include "WidgetModuleHUD.generated.h"

/** 
* This enums stores the types flag when returning a get widget method call.
* We have two types of returning, one for when the widget was found on the 
* ActiveWidgets list and another if the widget to get was not found.
*/
UENUM(BlueprintType)
enum EOutputGetWidget
{
	Found UMETA(DisplayName = "Found"),
	NotFound UMETA(DisplayName = "Not Found")
};

/**
* Main class that deals with the widgets manipulation. 
* This is implemented as a HUD as is one of the main interface components for
* this system.
* 
* Handles the creation and management of widgets inherited 
* from UUserWidgetBase. Thus, here we can create widgets, get widgets, show
* all widgets, hide all widgets and etc.
*/
UCLASS(Blueprintable)
class WIDGETMODULE_API AWidgetModuleHUD : public AHUD
{
	GENERATED_BODY()

public:
	/** Default constructor */
	AWidgetModuleHUD();

public:
	/** 
	* Process the widgets on the registry settings.
	* These settings may be of creation and show upon initialization.
	* 
	* @see FWidgetSettings
	*/
	UFUNCTION(BlueprintCallable)
	virtual void ProcessWidgetsOnRegistrySettings();

	/**
	* Creates a widget by it's name, if it exists in the registry list.
	* @note The widget's name must be the same as the one set on the registry.
	* 
	*  @param WidgetName The name of the widget on the registry to create
	*  @return Created widget. If it already exists, returns nullptr
	*/
	UFUNCTION(BlueprintCallable)
	virtual UUserWidgetBase* CreateWidgetByName(const FString& WidgetName);

	/**
	* Creates a widget by the giving name and it's class
	* It works separately from the registry list. Thus, this widget may not
	* be on the registry list of widgets.
	*
	* @param WidgetName	The name of the widget to create
	* @param WidgetClass The class of the widget to create
	*/
	UFUNCTION(BlueprintCallable)
	virtual UUserWidgetBase* CreateWidgetByNameAndClass
		(const FString& WidgetName, TSubclassOf<UUserWidgetBase> WidgetClass);

public:
	/**
	* Show a widget by it's name. 
	* It will get the widget on the active widgets list and set is visibility.
	* Note that this widget must already be created.
	* 
	* @param WidgetName The name of the widget to show
	*/
	UFUNCTION(BlueprintCallable)
	virtual void ShowWidgetByName(const FString& WidgetName) const;

	/** Show all the active widgets */
	UFUNCTION(BlueprintCallable)
	virtual void ShowAllWidgets() const;

	/** Hide all the active widgets */
	UFUNCTION(BlueprintCallable)
	virtual void HideAllWidgets() const;

	/** Hides and destroys all the active widgets */
	UFUNCTION(BlueprintCallable)
	virtual void DestroyAllWidgets();

public:
	/** 
	* Get the widget by it's name from the active widgets list. 
	* This is the BP version of this call as we expand the "Output" parameter
	* as execs. It may return "Found" or "NotFound".
	* 
	* @param Output Exec as the widget was found or not
	* @param WidgetName The name of the widget to get from active widgets
	* 
	* @return The widget reference (if found)
	*/
	UFUNCTION(BlueprintCallable, Meta = (ExpandEnumAsExecs = "Output"))
	virtual UUserWidgetBase* GetWidgetByName
		(TEnumAsByte<EOutputGetWidget>& Output, const FString& WidgetName);

	/**
	* Get the widget by it's class reference from the active widgets list.
	* This is the BP version of this call as we expand the "Output" parameter
	* as execs. It may return "Found" or "NotFound".
	*
	* @param Output Exec as the widget was found or not
	* @param WidgetClass The widget class to get the widget
	*
	* @return The widget reference (if found)
	*/
	UFUNCTION(BlueprintCallable, Meta = (ExpandEnumAsExecs = "Output",
		DeterminesOutputType = "WidgetClass"))
	virtual UUserWidgetBase* GetWidgetByClass
		(TEnumAsByte<EOutputGetWidget>& Output,
		UPARAM(meta = (AllowAbstract = "false"))
		const TSubclassOf<UUserWidgetBase> WidgetClass);

public:
	/** Returns true if there are any active widgets on the list */
	UFUNCTION(BlueprintPure)
	inline bool HasAnyActiveWidgets() const
		{ return ActiveWidgets.Num() > 0; }

	/**
	* Check if the widget is valid against the registry list by it's name.
	* It will check the name length, the registry property and the class
	* set for this widget name (if it exists).
	*
	* @param WidgetName The name of the widget to check on the registry
	* @return True if the widget is valid in the registry list, false otherwise
	*/
	UFUNCTION(BlueprintPure)
	bool IsWidgetNameValidOnWidgetRegistry(const FString& WidgetName) const;

	/**
	* Check if the widget is active in the widgets list by it's name.
	* A widget is active if:
	*		1. There is at least one active widget
	*		2. The active widget's least contains this widget's name
	*		3. The active widget's object is not nullptr
	* 
	* @param WidgetName The name of the widget to check
	* @return True if the widget is active, false otherwise
	*/
	UFUNCTION(BlueprintPure)
	bool IsWidgetActive(const FString& WidgetName) const;

public:
	/**
	* Get the widget by it's name from the active widgets list.
	* 
	* @param WidgetName The name of the widget to get from active widgets
	* @return The widget reference (if found) and nullptr otherwise
	*/
	UE_NODISCARD virtual UUserWidgetBase* GetWidgetByName
		(const FString& WidgetName) const;

	/**
	* Get the widget by it's name from the active widgets list 
	* and return it as the given type.
	*
	* @param WidgetName The name of the widget to get from active widgets
	* @return The widget reference (if found and cast success).
	* nullptr otherwise
	*/
	template <typename WidgetBaseType = UUserWidgetBase>
	UE_NODISCARD WidgetBaseType* GetWidgetByName
		(const FString& WidgetName) const
		{ return Cast<WidgetBaseType>(GetWidgetByName(WidgetName)); }

	/**
	* Get the widget by it's class from the active widgets list.
	*
	* @param WidgetClass The widget class to get the widget
	* @return The widget reference (if found) and nullptr otherwise
	*/
	UE_NODISCARD virtual UUserWidgetBase* GetWidgetByClass
		(TSubclassOf<UUserWidgetBase> WidgetClass) const;

	/**
	* Get the widget by it's class from the active widgets list
	* and return it as the given type.
	*
	* @param WidgetClass The widget class to get the widget
	* @return The widget reference (if found) and nullptr otherwise
	*/
	template <typename WidgetBaseType=UUserWidgetBase>
	UE_NODISCARD WidgetBaseType* GetWidgetByClass
		(const TSubclassOf<UUserWidgetBase> WidgetClass) const
		{ return Cast<WidgetBaseType>(GetWidgetByClass(WidgetClass)); }

public:
	/**
	* Tries to get the widget of the given type by name.
	* 
	* @param WidgetName The name of the widget
	* @param OutWidget The widget of the given type
	* 
	* @return True if the widget was found, false otherwise
	*/
	template <typename WidgetBaseType=UUserWidgetBase>
	bool TryGetWidgetByName(const FString& WidgetName, 
		WidgetBaseType*& OutWidget) const
	{
		OutWidget = Cast<WidgetBaseType>(GetWidgetByName(WidgetName));
		return OutWidget != nullptr;
	}

	/**
	* Tries to get the widget of the given type by a given class.
	*
	* @param WidgetClass The class of the widget
	* @param OutWidget The widget of the given type
	* 
	* @return True if the widget was found, false otherwise
	*/
	template <typename T=UUserWidgetBase>
	bool TryGetWidgetByClass
		(const TSubclassOf<UUserWidgetBase> WidgetClass, T*& OutWidget) const
	{
		OutWidget = GetWidgetByClass<T>(WidgetClass);
		return OutWidget != nullptr;
	}

protected:
	/** PostInitializeComponents */
	virtual void PostInitializeComponents() override;

	/**
	* Tries to create a new widget from it's name by consulting it's settings
	* (and thus, it's class) on the widget's registry.
	* 
	* @param InWidgetName The name of the widget
	* @param OutWidget The created widget
	* 
	* @return True if the widget was created, false otherwise
	*/
	virtual bool TryCreateWidget(const FString& InWidgetName, 
		UUserWidgetBase*& OutWidget);

protected:
	/** 
	* The widget registry list.
	* Contains the list of widget's name and widget's settings .
	*/
	UPROPERTY(EditAnywhere, Category = "WidgetManager")
	class UWidgetRegistryAsset* WidgetCatalog = nullptr;

	/** Map of current active widgets created (and managed) by this HUD. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<FString, UUserWidgetBase*> ActiveWidgets;
};
