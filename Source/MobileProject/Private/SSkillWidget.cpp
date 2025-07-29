// Fill out your copyright notice in the Description page of Project Settings.


#include "SSkillWidget.h"
#include "GameFramework/HUD.h"
#include "MenuHUD.h"
#include "Framework/Application/SlateApplication.h"
#include "../../../../Plugins/Experimental/MeshModelingToolsetExp/Source/ModelingUI/Public/ModelingWidgets/SDraggableBox.h"
#include "DragAndDrop/DecoratedDragDropOp.h"

void SSkillWidget::Construct(const FArguments& InArgs)
{
	bCanSupportFocus = true;
	OwningHUD = InArgs._OwningHUD;

	const int32 GridSize = 5;
	const float SlotSize = 100.0f;
	const float SlotPadding = 4.0f;
	const FMargin ContentPadding = FMargin(10.f);

	ChildSlot
	[
		SNew(SBox)
		.HeightOverride(300.f) // 고정된 높이
		[
			SNew(SScrollBox)
			.Orientation(Orient_Vertical)
			+ SScrollBox::Slot()
			[
				SNew(STextBlock).Text(FText::FromString("항목 1"))
			]
			+ SScrollBox::Slot()
			[
				SNew(STextBlock).Text(FText::FromString("항목 2"))
			]
			// 계속 추가 가능
		]
	];

}
