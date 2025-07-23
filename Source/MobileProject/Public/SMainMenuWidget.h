#pragma once
#include "SlateBasics.h"
#include "SlateExtras.h"

/**
 * 
 */
class SMainMenuWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SMainMenuWidget) {}

	SLATE_ARGUMENT(TWeakObjectPtr<class AMenuHUD>, OwningHUD)

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	FReply OnPlayClicked() const;
	FReply OnQuitClicked() const;

	TWeakObjectPtr<class AMenuHUD> OwningHUD;

	virtual bool SupportsKeyboardFocus() const override { return true; };

	FSlateBrush InvenButtonBrush;
	FSlateBrush SettingsButtonBrush;
	FSlateBrush SkillButtonBrush;
};