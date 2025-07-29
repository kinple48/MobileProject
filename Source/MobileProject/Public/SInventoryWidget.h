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
class MOBILEPROJECT_API SInventoryWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SInventoryWidget) {}

	SLATE_ARGUMENT(TWeakObjectPtr<class AMenuHUD>, OwningHUD)
	SLATE_ARGUMENT(TWeakObjectPtr<class AMobileProjectCharacter>, OwnerCharacter)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	virtual bool SupportsKeyboardFocus() const override { return true; };

	TWeakObjectPtr<class AMenuHUD> OwningHUD;
	//TSharedRef<SWidget> CreateInventoryItem(FText ItemName);
	TSharedRef<SWidget> GenerateRow(int32 RowIndex, int32 Columns, float SlotSize, float Padding);

	//virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	//virtual FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;

	FText Name;
};
