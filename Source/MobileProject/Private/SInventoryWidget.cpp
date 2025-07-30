// Fill out your copyright notice in the Description page of Project Settings.


#include "SInventoryWidget.h"
#include "GameFramework/HUD.h"
#include "MenuHUD.h"
#include "Framework/Application/SlateApplication.h"
#include "../../../../Plugins/Experimental/MeshModelingToolsetExp/Source/ModelingUI/Public/ModelingWidgets/SDraggableBox.h"

void SInventoryWidget::Construct(const FArguments& InArgs)
{
	bCanSupportFocus = true;
	OwningHUD = InArgs._OwningHUD;

	UTexture2D* XTex = LoadObject<UTexture2D>(nullptr, TEXT("/Game/TopDown/Image/x.x"));
	if (XTex)
	{
		XButtonBrush.SetResourceObject(XTex);
		XButtonBrush.ImageSize = FVector2D(50, 50);
	}

	const int32 GridSize = 5;
	const float SlotSize = 100.0f;
	const float SlotPadding = 4.0f;
	const FMargin ContentPadding = FMargin(4.f);

	TSharedRef<SVerticalBox> InventoryGrid = SNew(SVerticalBox);

	for (int32 Row = 0; Row < GridSize+1; ++Row)
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
			SNew(SBox)
			.WidthOverride(600.f)
			.HeightOverride(700.f)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(SVerticalBox)
				+SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew(SBorder)
					.BorderImage(FCoreStyle::Get().GetBrush("GenericWhiteBox"))
					.BorderBackgroundColor(FLinearColor(0.f, 0.f, 0.f, 0.4f))
					[
						SNew(SHorizontalBox)
						+SHorizontalBox::Slot()
						.HAlign(HAlign_Center)
						.VAlign(VAlign_Center)
						[
							SNew(STextBlock)
							.Text(FText::FromString(TEXT("Item")))
							.Font(FCoreStyle::GetDefaultFontStyle("Bold", 20))
						]
						+SHorizontalBox::Slot()
						.HAlign(HAlign_Right)
						.VAlign(VAlign_Center)
						.AutoWidth()
						.Padding(0.f,0.f,5.f,0.f)
						[
							SNew(SButton)
							.ButtonStyle(FCoreStyle::Get(), "NoBorder")
							.OnClicked(this, &SInventoryWidget::OnXButtonClicked)
							[
								SNew(SImage)
								.Image(&XButtonBrush)
							]
						]
					]
				
				]
				+SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew(SBorder)
					.BorderImage(FCoreStyle::Get().GetBrush("GenericWhiteBox"))
					.BorderBackgroundColor(FLinearColor(0.f, 0.f, 0.f, 0.8f))
					[
						InventoryGrid
					]
				]
			]
		]
	];
}

TSharedRef<SWidget> SInventoryWidget::GenerateRow(int32 RowIndex, int32 Columns, float SlotSize, float Padding)
{
	TSharedRef<SHorizontalBox> RowBox = SNew(SHorizontalBox);

	for (int32 Col = 0; Col < Columns; ++Col)
	{
		int32 SlotIndex = RowIndex * Columns + Col;
		FString ItemName = FString::Printf(TEXT("Slot %d"), SlotIndex + 1);

		RowBox->AddSlot()
		.AutoWidth()
		.Padding(Padding,0.f,Padding,0.f)
		[
			SNew(SBorder)
			.BorderImage(FCoreStyle::Get().GetBrush("GenericWhiteBox"))
			.BorderBackgroundColor(FLinearColor::Gray) 
			[
				SNew(SBox)
				.WidthOverride(SlotSize)
				.HeightOverride(SlotSize)
				[
					SNew(STextBlock)
					.Text(FText::FromString(ItemName))
					.Justification(ETextJustify::Center)
				
				]
			]
		];
	}

	return RowBox;
}

FReply SInventoryWidget::OnXButtonClicked() const
{
	if (OwningHUD.IsValid())
    {
        OwningHUD->CloseInvenWidget();
    }
    return FReply::Handled();
}