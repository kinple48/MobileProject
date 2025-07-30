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
	SLATE_ARGUMENT(TWeakObjectPtr<class AMobileProjectCharacter>, OwnerCharacter)

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	FReply OnInvenClicked() const;
	FReply OnSkillClicked() const;

	TWeakObjectPtr<class AMenuHUD> OwningHUD;
	TWeakObjectPtr<class AMobileProjectCharacter> OwnerCharacter;

	virtual bool SupportsKeyboardFocus() const override { return true; };

	FSlateBrush InvenButtonBrush;
	FSlateBrush SettingsButtonBrush;
	FSlateBrush SkillButtonBrush;
	FSlateBrush QuickSlotBrush;
	FSlateBrush ASkillBrush;
	FSlateBrush BSkillBrush;
	FSlateBrush CSkillBrush;

	FReply OnASkillClicked() const;
	FReply OnBSkillClicked() const;
	FReply OnCSkillClicked() const;
};