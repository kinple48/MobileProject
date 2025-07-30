// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "SlateBasics.h"
#include "SlateExtras.h"
#include "SlateCore.h"
#include "CoreMinimal.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SCompoundWidget.h"
#include "Input/Reply.h"           // FReply
#include "Input/Events.h"   

/**
 * 
 */
class MOBILEPROJECT_API SSkillWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSkillWidget) {}

	SLATE_ARGUMENT(TWeakObjectPtr<class AMenuHUD>, OwningHUD)
	SLATE_ARGUMENT(TWeakObjectPtr<class AMobileProjectCharacter>, OwnerCharacter)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	virtual bool SupportsKeyboardFocus() const override { return true; };

	TWeakObjectPtr<class AMenuHUD> OwningHUD;

	FSlateBrush XButtonBrush;
	FSlateBrush PlusButtonBrush;
	FSlateBrush MinusButtonBrush;

	TSharedRef<SWidget> CreateSkillEntry(const FString& SkillName);
	FSlateBrush SkillButtonBrush;
	FButtonStyle CustomStyle = FCoreStyle::Get().GetWidgetStyle<FButtonStyle>("Button");

	TArray<int32> LevelUpPointTable;
	TMap<FString, int32> SkillLevels;
	FString SelectedSkillName;
	TMap<FString, FString> SkillImagePathMap;
	TMap<FString, FSlateBrush> SkillBrushMap;

	FText GetSkillLevelText(const FString& SkillName) const;
    FReply OnIncreaseClicked(const FString& SkillName);
    FReply OnDecreaseClicked(const FString& SkillName);
	FReply OnXButtonClicked() const;
	FReply OnResetSkillClicked();
	FReply OnSaveSkillClicked();
	FReply OnSkillClicked(FString SkillName);

	int32 MaxSkillPoints = 367;
	int32 TotalSkillPoints = MaxSkillPoints;
};