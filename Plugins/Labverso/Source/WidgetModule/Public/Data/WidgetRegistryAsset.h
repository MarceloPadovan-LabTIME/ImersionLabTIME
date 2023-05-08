// 2023 Copyright Labverso, Brazil. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WidgetRegistryAsset.generated.h"

/** 
* This struct holds the settings for a widget.
* This settings will be used for creating widgets, 
* especially during the HUD's initialization.
*/
USTRUCT(BlueprintType)
struct WIDGETMODULE_API FWidgetSettings
{
	GENERATED_BODY()

public:
	/** The widget class to create */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, 
		meta=(ToolTip="The widget class to create"))
	TSubclassOf<UUserWidget> Class;

	/** If true, the widget will be created on the game's start */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, 
		meta=(ToolTip="If true, the widget will be created on start"))
	bool bCreateOnStart = false;

	/** If true, the widget will be shown on the game's start */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, 
		meta=(ToolTip="If true, the widget will be shown on start"))
	bool bShowOnStart = false;
};

/** 
* This is the data asset that stores a registry of widget 
* that can be created by a HUD.
* 
* This registry will contain the name of the widget (chosen by the developer) 
* and the widget settings for creation. 
* Any given HUD can have a WidgetRegistry of all widgets it can create.
*/
UCLASS(BlueprintType)
class WIDGETMODULE_API UWidgetRegistryAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	/** The widget registry list */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, 
		meta = (ToolTip = "The widget resgitry list"))
	TMap<FString, FWidgetSettings> Registries;
};
