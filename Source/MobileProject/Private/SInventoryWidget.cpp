// Fill out your copyright notice in the Description page of Project Settings.


#include "SInventoryWidget.h"
#include "GameFramework/HUD.h"
#include "MenuHUD.h"
#include "../../../../Plugins/Experimental/MeshModelingToolsetExp/Source/ModelingUI/Public/ModelingWidgets/SDraggableBox.h"

void SInventoryWidget::Construct(const FArguments& InArgs)
{
	bCanSupportFocus = true;

	OwningHUD = InArgs._OwningHUD;

	ChildSlot
		[
			SNew(SBorder)
			.BorderBackgroundColor(FLinearColor::Green)  // ³ì»ö ¹è°æ
			[
				SNew(SDraggableBox)
			]
		];
}
