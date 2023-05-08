// 2023 Labverso, Brazil. Imersion Test.

#pragma once

#include "CoreMinimal.h"
#include "WidgetModuleHUD.h"
#include "MainHUD.generated.h"

/**
* This is the game main HUD.
*/
UCLASS()
class LABTIMEIMERSIONTEST_API AMainHUD : public AWidgetModuleHUD
{
	GENERATED_BODY()
	
public:
	/** 
	* Toggles the visualization of the scoreboard widget.
	* 
	* @note This method will actually be implemeted in the Blueprint
	* @param bActive If true will show the widget. If false will hide it
	* @return True if the operation was successful
	*/
	UFUNCTION(BlueprintImplementableEvent)
	bool ToggleScoreboardWidget(bool bActive);
};
