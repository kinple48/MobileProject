// Fill out your copyright notice in the Description page of Project Settings.


#include "SOptionWidget.h"
#include "GameFramework/HUD.h"
#include "MenuHUD.h"
#include "Framework/Application/SlateApplication.h"
#include "../../../../Plugins/Experimental/MeshModelingToolsetExp/Source/ModelingUI/Public/ModelingWidgets/SDraggableBox.h"
#include "DragAndDrop/DecoratedDragDropOp.h"

void SOptionWidget::Construct(const FArguments& InArgs)
{
	bCanSupportFocus = true;
	OwningHUD = InArgs._OwningHUD;

	const int32 GridSize = 5;
	const float SlotSize = 100.0f;
	const float SlotPadding = 4.0f;
	const FMargin ContentPadding = FMargin(10.f);

	TSharedRef<SVerticalBox> InventoryGrid = SNew(SVerticalBox);

	for (int32 Row = 0; Row < GridSize; ++Row)
	{
		InventoryGrid->AddSlot()
		.AutoHeight()
		.Padding(0, SlotPadding)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.HAlign(HAlign_Left)
			.AutoWidth()
			[
				GenerateRow(Row, GridSize, SlotSize, SlotPadding)
			]
		];
	}

	ChildSlot
	[
		SNew(SOverlay)
		+ SOverlay::Slot()
		.HAlign(HAlign_Right)
		.VAlign(VAlign_Center)
		.Padding(ContentPadding)
		[
			SNew(SBorder)
			.BorderImage(FCoreStyle::Get().GetBrush("GenericWhiteBox"))
			.BorderBackgroundColor(FLinearColor::Black) 
			.Padding(20.f)
			[
				SNew(SBox)
				.WidthOverride(600.f)
				.HeightOverride(600.f)
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)
				[
					InventoryGrid
				]
			]
		]
	];
}

TSharedRef<SWidget> SOptionWidget::GenerateRow(int32 RowIndex, int32 Columns, float SlotSize, float Padding)
{
	TSharedRef<SHorizontalBox> RowBox = SNew(SHorizontalBox);

	for (int32 Col = 0; Col < Columns; ++Col)
	{
		int32 SlotIndex = RowIndex * Columns + Col;
		FString ItemName = FString::Printf(TEXT("Slot %d"), SlotIndex + 1);

		RowBox->AddSlot()
		.AutoWidth()
		.Padding(Padding)
		[
			SNew(SBox)
			.WidthOverride(SlotSize)
			.HeightOverride(SlotSize)
			[
				SNew(SDraggableBox)
				[
					SNew(SButton)
					.ButtonColorAndOpacity(FLinearColor::Gray)
					[
						SNew(STextBlock)
						.Text(FText::FromString(ItemName))
						.Justification(ETextJustify::Center)
					]
				]
			]
		];
	}

	return RowBox;
}
