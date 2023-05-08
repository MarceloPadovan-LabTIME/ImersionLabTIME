// 2023 Copyright Labverso, Brazil. All Rights Reserved.

#include "WidgetModuleHUD.h"

#include "Components/SlateWrapperTypes.h"
#include "Data/WidgetRegistryAsset.h"
#include "WidgetModule/WidgetModuleLogDeclaration.h"
#include "Widget/UserWidgetBase.h"

AWidgetModuleHUD::AWidgetModuleHUD()
{
	PrimaryActorTick.bCanEverTick = false;
	bShowHUD = false;
}

void AWidgetModuleHUD::PostInitializeComponents()
{
	// Process the widgets that are on the registry settings
	// This settings may create and show widget upon initialization
	ProcessWidgetsOnRegistrySettings();

	Super::PostInitializeComponents();
}

void AWidgetModuleHUD::ProcessWidgetsOnRegistrySettings()
{
	// If we do not have a widget registry:
	if (!WidgetCatalog)
	{
		UE_LOG(LogWidgetModule, Error, TEXT("No widget registry to process."));
		return;
	}

	// Foreach widget on the registry:
	for (const auto& WidgetRegistry : WidgetCatalog->Registries)
	{
		// Get the widget name and settings from the registry
		const FString WidgetName = WidgetRegistry.Key;
		const FWidgetSettings WidgetSettings = WidgetRegistry.Value;

		// Check if the widget should be created on start
		if (!WidgetSettings.bCreateOnStart)
		{
			continue;
		}

		// Check if the widget is already active
		if (IsWidgetActive(WidgetName))
		{
			continue;
		}

		// Try to create the widget
		UUserWidgetBase* NewWidget = nullptr;
		TryCreateWidget(WidgetName, NewWidget);

		// Check if creation was succesful
		if (!NewWidget)
		{
			UE_LOG(LogWidgetModule, Error, TEXT("Could not create widget '%s'\
				upon initialization."), *WidgetName);
			continue;
		}

		// If we should show widget on start, show it
		WidgetSettings.bShowOnStart
			? NewWidget->ShowWidget()
			: NewWidget->HideWidget();
	}
}

UUserWidgetBase* AWidgetModuleHUD::CreateWidgetByName
	(const FString& WidgetName)
{
	// Try to create the widget by it's name
	UUserWidgetBase* Widget = nullptr;
	const bool bWasCreationSuccess = TryCreateWidget(WidgetName, Widget);

	// If the creation was not success, return nullptr
	if (!bWasCreationSuccess)
	{
		return nullptr;
	}

	return Widget;
}

UUserWidgetBase* AWidgetModuleHUD::CreateWidgetByNameAndClass
	(const FString& WidgetName, const TSubclassOf<UUserWidgetBase> WidgetClass)
{
	// Check if the widget name is valid against the registry
	if (WidgetClass == nullptr)
	{
		UE_LOG(LogWidgetModule, Warning,
			TEXT("Could not create widget '%s' as class is null."), 
			*WidgetName);
		return nullptr;
	}

	// Check if there's already a widget with this name active
	if (IsWidgetActive(WidgetName))
	{
		UE_LOG(LogWidgetModule, Error,
			TEXT("Widget with name '%s' is already active."), *WidgetName);
		return nullptr;
	}

	// Create the widgget from it's class
	auto* Widget = CreateWidget<UUserWidgetBase>(GetWorld(), *WidgetClass);
	if (!Widget)
	{
		UE_LOG(LogWidgetModule, Error,
			TEXT("Error during creating of widget with name '%s'."), 
			*WidgetName);
		return nullptr;
	}

	// Setup new widget data
	Widget->SetOwningHUD(this);
	Widget->AddToViewport();

	// Add the widget to ActiveWidgets
	ActiveWidgets.Add(WidgetName, Widget);
	return Widget;
}

bool AWidgetModuleHUD::TryCreateWidget(const FString& InWidgetName, 
	UUserWidgetBase*& OutWidget)
{
	// Check if there's already a widget active with this name
	if (IsWidgetActive(InWidgetName))
	{
		UE_LOG(LogWidgetModule, Error, 
			TEXT("Widget with name '%s' is already active."), *InWidgetName);
		return false;
	}

	// Check if the widget name is valid against the widget registry
	if (!IsWidgetNameValidOnWidgetRegistry(InWidgetName))
	{
		return false;
	}

	// Get the widget class from the registry list
	const auto& WidgetToCreate = WidgetCatalog->Registries[InWidgetName];

	// Create the widget by it's class
	OutWidget = CreateWidget<UUserWidgetBase>(GetWorld(), 
		*WidgetToCreate.Class);

	// Check if the widget was created
	if (!OutWidget)
	{
		UE_LOG(LogWidgetModule, Error, 
			TEXT("Error during creating of widget with name '%s'."), 
			*InWidgetName);
		return false;
	}

	// Setup new widget data
	OutWidget->SetOwningHUD(this);
	OutWidget->AddToViewport();

	// Add the widget to ActiveWidgets
	ActiveWidgets.Add(InWidgetName, OutWidget);

	return true;
}

UUserWidgetBase* AWidgetModuleHUD::GetWidgetByName
	(const FString& WidgetName) const
{
	// Check if there's any active widget
	if (!HasAnyActiveWidgets())
	{
		UE_LOG(LogWidgetModule, Error, TEXT("Could not get widget '%s' as\
			there are no active widgets."), *WidgetName);
		return nullptr;
	}

	if (WidgetName.IsEmpty())
	{
		UE_LOG(LogWidgetModule, Error, TEXT("Could not get widget as widget's\
			name is empty"));
		return nullptr;
	}

	// Check if the widget is already created on ActiveWidgets
	for (const auto& ActiveWidget : ActiveWidgets)
	{
		// If the name of the active widget is different, ignore
		const FString ActiveWidgetName = ActiveWidget.Key;
		if (!ActiveWidgetName.Equals(WidgetName))
		{
			continue;
		}

		// If found the widget, return it
		return ActiveWidget.Value;
	}

	UE_LOG(LogWidgetModule, Error, TEXT("Could not get widget '%s' as it\
		could not be found on active widgets list."), *WidgetName);
	return nullptr;
}

UUserWidgetBase* AWidgetModuleHUD::GetWidgetByName
	(TEnumAsByte<EOutputGetWidget>& Output, const FString& WidgetName)
{
	if (auto* Widget = GetWidgetByName(WidgetName))
	{
		Output = EOutputGetWidget::Found;
		return Widget;
	}

	Output = EOutputGetWidget::NotFound;
	return nullptr;
}

UUserWidgetBase* AWidgetModuleHUD::GetWidgetByClass
	(const TSubclassOf<UUserWidgetBase> WidgetClass) const
{
	// Check if there's any active widget
	if (!HasAnyActiveWidgets())
	{
		UE_LOG(LogWidgetModule, Error, TEXT("Could not get widget by class\
			'%s' as there are no active widgets."), *WidgetClass->GetName());
		return nullptr;
	}

	if (WidgetClass == nullptr)
	{
		UE_LOG(LogWidgetModule, Error, TEXT("Could not get widget by class\
			as class is nullptr"));
		return nullptr;
	}

	// Check if the widget is already created on ActiveWidgets
	for (const auto& ActiveWidget : ActiveWidgets)
	{
		// Check if the active widget's class is the same we're looking for
		const auto& Widget = ActiveWidget.Value;
		if (!Widget->IsA(WidgetClass))
		{
			continue;
		}

		// If found the widget, return it
		return Widget;
	}

	return nullptr;
}

UUserWidgetBase* AWidgetModuleHUD::GetWidgetByClass
	(TEnumAsByte<EOutputGetWidget>& Output,
	const TSubclassOf<UUserWidgetBase> WidgetClass)
{
	if (auto* Widget = GetWidgetByClass(WidgetClass))
	{
		Output = EOutputGetWidget::Found;
		return Widget;
	}

	Output = EOutputGetWidget::NotFound;
	return nullptr;
}

void AWidgetModuleHUD::ShowWidgetByName(const FString& WidgetName) const
{
	// Check if there's any active widget
	if (!IsWidgetActive(WidgetName))
	{
		UE_LOG(LogWidgetModule, Error, TEXT("Widget to show with name '%s'\
			is not active."), *WidgetName);
		return;
	}

	// Check if the widget is already created on ActiveWidgets
	for (const auto& ActiveWidgetData : ActiveWidgets)
	{
		// Get the active widget's name
		const auto& ActiveWidgetName = ActiveWidgetData.Key;

		// If it's not the widget we are looking for, ignore
		if (!ActiveWidgetName.Equals(WidgetName))
		{
			continue;
		}

		// If found the widget, show it by setting it's visibility to visible
		ActiveWidgetData.Value->SetVisibility(ESlateVisibility::Visible);
		return;
	}

	UE_LOG(LogWidgetModule, Error, TEXT("Widget to show with name '%s'\
		is not active."), *WidgetName);
}

void AWidgetModuleHUD::ShowAllWidgets() const
{
	// Check if there's active widgets
	if (!HasAnyActiveWidgets())
	{
		UE_LOG(LogWidgetModule, Warning, TEXT("No active widgets found\
			when showing all active widgets"));
		return;
	}

	// Show all widgets
	for (const auto& ActiveWidget : ActiveWidgets)
	{
		const auto& Widget = ActiveWidget.Value;
		Widget->ShowWidget();
	}
}

void AWidgetModuleHUD::HideAllWidgets() const
{
	// Check if there's active widgets
	if (!HasAnyActiveWidgets())
	{
		UE_LOG(LogWidgetModule, Warning, TEXT("No active widgets found\
			when hiding all active widgets."));
		return;
	}

	// Hide all active widgets
	for (const auto& ActiveWidget : ActiveWidgets)
	{
		const auto& Widget = ActiveWidget.Value;
		Widget->HideWidget();
	}
}

void AWidgetModuleHUD::DestroyAllWidgets()
{
	if (!HasAnyActiveWidgets())
	{
		UE_LOG(LogWidgetModule, Warning, TEXT("No active widgets found\
			when destroying all active widgets."));
		return;
	}

	// Destroy all widgets
	for (const auto& ActiveWidget : ActiveWidgets)
	{
		const auto& Widget = ActiveWidget.Value;
		Widget->RemoveFromParent();
	}

	// Clear the ActiveWidgets
	ActiveWidgets.Empty();
}

bool AWidgetModuleHUD::IsWidgetNameValidOnWidgetRegistry(const FString& WidgetName) const
{
	// Check if the widget name is empty
	if (WidgetName.IsEmpty())
	{
		UE_LOG(LogWidgetModule, Error, TEXT("Widget name is empty."));
		return false;
	}

	// Check if we have a widget registry
	if (!WidgetCatalog)
	{
		UE_LOG(LogWidgetModule, Error, TEXT("Widget registry is not valid."));
		return false;
	}

	// Check if the widget registry contains a widget with this name
	if (!WidgetCatalog->Registries.Contains(WidgetName))
	{
		UE_LOG(LogWidgetModule, Error, 
			TEXT("Widget with name '%s' is not in the registry list."), 
			*WidgetName);
		return false;
	}

	// Check if the widget class is valid
	if (!WidgetCatalog->Registries[WidgetName].Class)
	{
		UE_LOG(LogWidgetModule, Error, 
			TEXT("Widget class at name '%s' is not valid."), *WidgetName);
		return false;
	}

	return true;
}

bool AWidgetModuleHUD::IsWidgetActive(const FString& WidgetName) const
{
	// Check if the widget name is empty
	if (WidgetName.IsEmpty())
	{
		UE_LOG(LogWidgetModule, Error, TEXT("Widget name is empty."));
		return false;
	}

	// A widget is active if:
	//		1. There is at least one active widget
	//		2. The active widget's least contains this widget's name
	//		3. The active widget's object is not nullptr
	const bool bIsWidgetActive = HasAnyActiveWidgets() && 
								 ActiveWidgets.Contains(WidgetName) && 
								 ActiveWidgets[WidgetName] != nullptr;

	// Return the flag
	return bIsWidgetActive;
}
