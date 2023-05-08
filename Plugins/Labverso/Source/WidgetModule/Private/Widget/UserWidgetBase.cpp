// 2023 Copyright Labverso, Brazil. All Rights Reserved.

#include "Widget/UserWidgetBase.h"

void UUserWidgetBase::ShowWidget()
{
	// Check if the widget is still valid and
	// if the widget is already the default
	if (!IsValid(this) || GetVisibility() == DefaultSlateVisibility)
	{
		return;
	}

	// Set the visibility to the default one
	SetVisibility(DefaultSlateVisibility);
}

void UUserWidgetBase::HideWidget()
{
	// Check if the widget is still valid and
	// if the widget is already hidden
	if (!IsValid(this) || GetVisibility() == ESlateVisibility::Hidden)
	{
		return;
	}

	// Set the visibility to hide the widget
	SetVisibility(ESlateVisibility::Hidden);
}

void UUserWidgetBase::ToggleWidgetVisibility()
{
	if (!IsValid(this))
	{
		return;
	}

	// If the widget is visible, hide it.
	if (GetVisibility() == ESlateVisibility::Visible)
	{
		SetVisibility(ESlateVisibility::Hidden);
		return;
	}

	// If the widget is hidden, show it
	// @note That this should be overwritten if the widget's default visibility
	// is not "Visible".This may block the player's input on the game as
	// a "Visible" visibility will be hit-testable and may break the interface.
	SetVisibility(ESlateVisibility::Visible);
}

void UUserWidgetBase::DestroyWidget()
{
	if (!IsValid(this))
	{
		return;
	}

	RemoveFromParent();
}
