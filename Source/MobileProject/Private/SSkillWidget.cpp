#include "SSkillWidget.h"
#include "GameFramework/HUD.h"
#include "MenuHUD.h"
#include "Framework/Application/SlateApplication.h"
#include "../../../../Plugins/Experimental/MeshModelingToolsetExp/Source/ModelingUI/Public/ModelingWidgets/SDraggableBox.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Widgets/Input/SButton.h"
#include "Styling/SlateTypes.h"

void SSkillWidget::Construct(const FArguments& InArgs)
{
	bCanSupportFocus = true;
	OwningHUD = InArgs._OwningHUD;

	if (UTexture2D* XTex = LoadObject<UTexture2D>(nullptr, TEXT("/Game/TopDown/Image/x.x")))
	{
		XButtonBrush.SetResourceObject(XTex);
		XButtonBrush.ImageSize = FVector2D(70, 70);
	}

	if (UTexture2D* PlusTex = LoadObject<UTexture2D>(nullptr, TEXT("/Game/TopDown/Image/+.+")))
	{
		PlusButtonBrush.SetResourceObject(PlusTex);
	}

	if (UTexture2D* MinusTex = LoadObject<UTexture2D>(nullptr, TEXT("/Game/TopDown/Image/-.-")))
	{
		MinusButtonBrush.SetResourceObject(MinusTex);
	}

	const FMargin ContentPadding = FMargin(10.f);

	TArray<FString> SkillNames = {
        TEXT("Skill A"),
        TEXT("Skill B"),
        TEXT("Skill C"),
        TEXT("Skill D"),
        TEXT("Skill E"),
        TEXT("Skill F"),
        TEXT("Skill G"),
        TEXT("Skill H"),
		TEXT("Skill I"),
		TEXT("Skill J"),
		TEXT("Skill K"),
		TEXT("Skill L"),
		TEXT("Skill M"),
		TEXT("Skill N"),
		TEXT("Skill O"),
		TEXT("Skill P")
    };

	SkillImagePathMap = {
		{ TEXT("Skill A"), TEXT("/Game/TopDown/Image/A.A") },
		{ TEXT("Skill B"), TEXT("/Game/TopDown/Image/B.B") },
		{ TEXT("Skill C"), TEXT("/Game/TopDown/Image/C.C") },
		{ TEXT("Skill D"), TEXT("/Game/TopDown/Image/D.D") },
		{ TEXT("Skill E"), TEXT("/Game/TopDown/Image/E.E") },
		{ TEXT("Skill F"), TEXT("/Game/TopDown/Image/F.F") },
		{ TEXT("Skill G"), TEXT("/Game/TopDown/Image/G.G") },
		{ TEXT("Skill H"), TEXT("/Game/TopDown/Image/H.H") },
		{ TEXT("Skill I"), TEXT("/Game/TopDown/Image/I.I") },
		{ TEXT("Skill J"), TEXT("/Game/TopDown/Image/J.J") },
		{ TEXT("Skill K"), TEXT("/Game/TopDown/Image/K.K") },
		{ TEXT("Skill L"), TEXT("/Game/TopDown/Image/L.L") },
		{ TEXT("Skill M"), TEXT("/Game/TopDown/Image/M.M") },
		{ TEXT("Skill N"), TEXT("/Game/TopDown/Image/N.N") },
		{ TEXT("Skill O"), TEXT("/Game/TopDown/Image/O.O") },
		{ TEXT("Skill P"), TEXT("/Game/TopDown/Image/P.P") }
	};

	for (const FString& Name : SkillNames)
	{
		FString* PathPtr = SkillImagePathMap.Find(Name);
		if (PathPtr)
		{
			UTexture2D* Tex = LoadObject<UTexture2D>(nullptr, **PathPtr);
			if (Tex)
			{
				FSlateBrush NewBrush;
				NewBrush.SetResourceObject(Tex);
				NewBrush.ImageSize = FVector2D(100, 100);
				SkillBrushMap.Add(Name, NewBrush);
			}
		}
	}

	LevelUpPointTable = {
		0,
		1,
		1,
		2,
		4,
		4,
		8,
		8,
		8,
		12
	};

	if (OwningHUD.IsValid() && OwningHUD->SavedSkillLevels.Num() > 0)
	{
		SkillLevels = OwningHUD->SavedSkillLevels;
		TotalSkillPoints = OwningHUD->SavedTotalSkillPoints;
	}
	else
	{
		for (const FString& SkillName : SkillNames)
        SkillLevels.Add(SkillName, 1);
		TotalSkillPoints = MaxSkillPoints;
	}

	TSharedRef<SVerticalBox> SkillList = SNew(SVerticalBox);

	for (const FString& SkillName : SkillNames)
    {
        SkillList->AddSlot()
        .Padding(FMargin(0, 0, 0, 15.f))
        .AutoHeight()
        [
            CreateSkillEntry(SkillName)
        ];
    }

	TSharedRef<SVerticalBox> SkillInfo = SNew(SVerticalBox);

	ChildSlot
	[
		SNew(SOverlay)
        + SOverlay::Slot()
        .HAlign(HAlign_Left)
        .VAlign(VAlign_Center)
        .Padding(ContentPadding)
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
						.Text(FText::FromString(TEXT("Skill")))
						.Font(FCoreStyle::GetDefaultFontStyle("Bold", 20))
					]
					+SHorizontalBox::Slot()
					.HAlign(HAlign_Right)
					.VAlign(VAlign_Center)
					.AutoWidth()
					.Padding(0.f,0.f,20.f,0.f)
					[
						SNew(SButton)
						.ButtonStyle(FCoreStyle::Get(), "NoBorder")
						.OnClicked(this, &SSkillWidget::OnXButtonClicked)
						[
							SNew(SImage)
							.Image(&XButtonBrush)
						]
					]
				]
			]
			+SVerticalBox::Slot()
			[
				SNew(SHorizontalBox)
				+SHorizontalBox::Slot()
				[
					SNew(SBorder)
					.BorderImage(FCoreStyle::Get().GetBrush("GenericWhiteBox"))
					.BorderBackgroundColor(FLinearColor(0.f, 0.f, 0.f, 0.8f))
					.Padding(20.f)
					[
						SNew(SBox)
						.WidthOverride(1000.f)
						.HeightOverride(1000.f)
						.HAlign(HAlign_Fill)
						.VAlign(VAlign_Fill)
						[
							SNew(SVerticalBox)
							+ SVerticalBox::Slot()
							.AutoHeight()
							.Padding(20.f)
							[
								SNew(SHorizontalBox)
								+SHorizontalBox::Slot()
								.HAlign(HAlign_Left)
								.VAlign(VAlign_Center)
								[
									SNew(STextBlock)
									.Text(FText::FromString(TEXT("Skill Point")))
									.Font(FCoreStyle::GetDefaultFontStyle("Bold", 20))
								]
								+SHorizontalBox::Slot()
								.HAlign(HAlign_Right)
								.VAlign(VAlign_Center)
								[
									SNew(STextBlock)
									.Text_Lambda([this]() {
										return FText::Format(
										FText::FromString(TEXT("{0}/{1}")),
										FText::AsNumber(TotalSkillPoints),
										FText::AsNumber(MaxSkillPoints)
										);
									})
									.Font(FCoreStyle::GetDefaultFontStyle("Bold", 20))
								]
							]
							+ SVerticalBox::Slot()
							[
								SNew(SScrollBox)
								.Orientation(Orient_Vertical)
								.ScrollBarAlwaysVisible(true)
								+ SScrollBox::Slot()
								.Padding(20.f, 0.f, 20.f, 0.f)
								[
									SkillList
								]
							]
							+ SVerticalBox::Slot()
							.Padding(10.f)
							.AutoHeight()
							.VAlign(VAlign_Center)
							[
								SNew(SHorizontalBox)
								+SHorizontalBox::Slot()
								.HAlign(HAlign_Left)
								[
									SNew(SBox)
									.WidthOverride(200.f)
									[
										SNew(SButton)
										.HAlign(HAlign_Center)
										.VAlign(VAlign_Center)
										.OnClicked(this, &SSkillWidget::OnResetSkillClicked)
										[
											SNew(STextBlock)
											.Text(FText::FromString(TEXT("Reset Skill")))
											.Font(FCoreStyle::GetDefaultFontStyle("Bold", 20))
										]
									]
								]
								+SHorizontalBox::Slot()
								.HAlign(HAlign_Right)
								[
									SNew(SBox)
									.WidthOverride(200.f)
									[
										SNew(SButton)
										.HAlign(HAlign_Center)
										.VAlign(VAlign_Center)
										.OnClicked(this, &SSkillWidget::OnSaveSkillClicked)
										[
											SNew(STextBlock)
											.Text(FText::FromString(TEXT("Save Skill")))
											.Font(FCoreStyle::GetDefaultFontStyle("Bold", 20))
										]
									]
								]
							]
						]
					]
				]
				+SHorizontalBox::Slot()
				[
					SNew(SBorder)
					.BorderImage(FCoreStyle::Get().GetBrush("GenericWhiteBox"))
					.BorderBackgroundColor(FLinearColor(0.f, 0.f, 0.f, 0.8f))
					.Padding(20.f)
					[
						SNew(SBox)
						.WidthOverride(1000.f)
						.HeightOverride(1000.f)
						.HAlign(HAlign_Fill)
						.VAlign(VAlign_Fill)
						[
							SNew(SBorder)
							.BorderImage(FCoreStyle::Get().GetBrush("GenericWhiteBox"))
							.BorderBackgroundColor(FLinearColor(0.15f, 0.15f, 0.15f, 1.f))
							.Padding(0.f,20.f,20.f,20.f)
							[
								SNew(SBox)
								.Padding(20.f)
								[
									SNew(STextBlock)
									.Text_Lambda([this]() {
										if (SelectedSkillName.IsEmpty())
										return FText::FromString(TEXT(""));
										return FText::Format(
										FText::FromString(TEXT("{0} Info")), 
										FText::FromString(SelectedSkillName)
										);
									})
									.Font(FCoreStyle::GetDefaultFontStyle("Regular", 24))
								]
							]
						]
					]
				]
			]
		]
	];

}

TSharedRef<SWidget> SSkillWidget::CreateSkillEntry(const FString& SkillName)
{
	FSlateFontInfo SkillFont = FCoreStyle::GetDefaultFontStyle("Regular", 20);

    // SkillName에 맞는 이미지 경로 찾기
    FString* ImagePathPtr = SkillImagePathMap.Find(SkillName);
    UTexture2D* SkillTex = nullptr;
    if (ImagePathPtr)
    {
        SkillTex = LoadObject<UTexture2D>(nullptr, **ImagePathPtr);
    }

	FSlateBrush* SkillBrush = SkillBrushMap.Find(SkillName);
	if (SkillBrush == nullptr)
		SkillBrush = &SkillButtonBrush;

    return SNew(SBorder)
        .BorderImage(FCoreStyle::Get().GetBrush("GenericWhiteBox"))
        .BorderBackgroundColor(FLinearColor(0.15f, 0.15f, 0.15f, 1.f))
        [
            SNew(SBox)
            .HeightOverride(150.f)
            [
                SNew(SButton)
                .ButtonStyle(&FCoreStyle::Get().GetWidgetStyle<FButtonStyle>("NoBorder"))
                .HAlign(HAlign_Fill)
                .ContentPadding(FMargin(0))
                .OnClicked_Lambda([this, SkillName]() { return this->OnSkillClicked(SkillName); })
                [
                    SNew(SHorizontalBox)
                    +SHorizontalBox::Slot()
                    .AutoWidth()
                    [
                        SNew(SBorder)
                        .BorderImage(SkillBrush)
                        [
                            SNew(SBox)
                            .WidthOverride(150.f)
                            .HeightOverride(150.f)
                            [
                                SNew(SOverlay)
                                + SOverlay::Slot()
                                [
                                    SNew(SDraggableBox)
                                    [
                                        SNew(SBox)
                                        [
                                            SNew(SImage).Image(SkillBrush)
                                        ]
                                    ]
                                ]
                            ]
                        ]
                    ]
				+ SHorizontalBox::Slot()
				.VAlign(VAlign_Center)
				[
					SNew(STextBlock)
					.Text(FText::FromString(SkillName))
					.Font(SkillFont)
					.Margin(FMargin(15.f, 0.f))
					.WrapTextAt(560.f)
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(FMargin(50.f, 0.f, 0.f, 0.f))
				[
					SNew(SBox)
					.WidthOverride(2.f)
					[
						SNew(SBorder)
						.BorderBackgroundColor(FLinearColor::Black)
						.BorderImage(FCoreStyle::Get().GetBrush("WhiteBrush"))
					]
				]
				+ SHorizontalBox::Slot()
				.VAlign(VAlign_Center)
				[
					SNew(SVerticalBox)
					+ SVerticalBox::Slot()
					.HAlign(HAlign_Center)
					[
						SNew(STextBlock)
						.Text_Lambda([this, SkillName]() {
							int32 CurLevel = 1;
							int32 RequiredPoint = 0;

							if(const int32* LevelPtr = SkillLevels.Find(SkillName))
							CurLevel = *LevelPtr;
							if (CurLevel < LevelUpPointTable.Num())
							RequiredPoint = LevelUpPointTable[CurLevel];
							else
							 RequiredPoint = 0;

							return FText::AsNumber(RequiredPoint);
						})
						.Font(SkillFont)
						.Margin(FMargin(15.f, 0.f))
						.WrapTextAt(560.f)
					]

					+ SVerticalBox::Slot()
					.HAlign(HAlign_Center)
					[
						SNew(STextBlock)
						.Text(FText::FromString(TEXT("Point")))
						.Font(SkillFont)
						.Margin(FMargin(15.f, 0.f))
						.WrapTextAt(560.f)
					]
				]
				+ SHorizontalBox::Slot()
				.VAlign(VAlign_Center)
				[
					SNew(SVerticalBox)
					+ SVerticalBox::Slot()
					.HAlign(HAlign_Center)
					[
						SNew(STextBlock)
						.Text_Lambda([this, SkillName]() { return this->GetSkillLevelText(SkillName); })
						.Font(FCoreStyle::GetDefaultFontStyle("Regular", 40))
						.Margin(FMargin(15.f, 0.f))
						.WrapTextAt(560.f)
					]

					+ SVerticalBox::Slot()
					.Padding(0.f,10.f,0.f,0.f)
					.HAlign(HAlign_Center)
					[
						SNew(STextBlock)
						.Text(FText::FromString(TEXT("Level")))
						.Font(FCoreStyle::GetDefaultFontStyle("Regular", 20))
						.Margin(FMargin(15.f, 0.f))
						.WrapTextAt(560.f)
					]
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.VAlign(VAlign_Center)
				.Padding(0.f,0.f,10.f,0.f)
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.Padding(0.f,0.f,20.f,0.f)
					[
						SNew(SBox)
						.WidthOverride(100)
						.HeightOverride(100)    
						[
							SNew(SButton)
							.OnClicked_Lambda([this, SkillName]() { return this->OnIncreaseClicked(SkillName); })
							.ButtonStyle(FCoreStyle::Get(), "NoBorder")
							[
								SNew(SImage)
								.Image(&PlusButtonBrush)
							]
						]
					]
					+ SHorizontalBox::Slot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					[
						SNew(SBox)
						.WidthOverride(100)
						.HeightOverride(100)    
						[
							SNew(SButton)
							.OnClicked_Lambda([this, SkillName]() { return this->OnDecreaseClicked(SkillName); })
							.ButtonStyle(FCoreStyle::Get(), "NoBorder")
							[
								SNew(SImage)
								.Image(&MinusButtonBrush)
							]
						]
					]
				]
			]
		]
	];
}

FText SSkillWidget::GetSkillLevelText(const FString& SkillName) const
{
	int32 Level = 0;
    const int32* LevelPtr = SkillLevels.Find(SkillName);
    if (LevelPtr)
    {
        Level = *LevelPtr;
    }
    return FText::AsNumber(Level);
}

FReply SSkillWidget::OnIncreaseClicked(const FString& SkillName)
{
	int32* LevelPtr = SkillLevels.Find(SkillName);
	if (!LevelPtr) return FReply::Handled();
	SelectedSkillName = SkillName;
	int32 CurLevel = *LevelPtr;
    int32 NextLevel = CurLevel + 1;

    if (CurLevel < 10)
    {
        int32 PointCost = LevelUpPointTable.IsValidIndex(CurLevel) ? LevelUpPointTable[CurLevel] : 0;
        if (TotalSkillPoints >= PointCost)
        {
            *LevelPtr = NextLevel;
            TotalSkillPoints -= PointCost;
        }
    }

    this->Invalidate(EInvalidateWidget::Layout);
    return FReply::Handled();
}

FReply SSkillWidget::OnDecreaseClicked(const FString& SkillName)
{
	int32* LevelPtr = SkillLevels.Find(SkillName);
	if (!LevelPtr) return FReply::Handled();
	SelectedSkillName = SkillName;
	int32 CurLevel = *LevelPtr;
    int32 PrevLevel = CurLevel - 1;

    if (CurLevel > 1)
    {
        int32 PointRefund = LevelUpPointTable.IsValidIndex(PrevLevel) ? LevelUpPointTable[PrevLevel] : 0;
        *LevelPtr = PrevLevel;
        TotalSkillPoints += PointRefund;
        if (TotalSkillPoints > MaxSkillPoints)
            TotalSkillPoints = MaxSkillPoints;
    }

    this->Invalidate(EInvalidateWidget::Layout);
    return FReply::Handled();
}

FReply SSkillWidget::OnXButtonClicked() const
{
	if (OwningHUD.IsValid())
    {
        OwningHUD->CloseSkillWidget();
    }
    return FReply::Handled();
}

FReply SSkillWidget::OnResetSkillClicked()
{
    for (auto& Elem : SkillLevels)
    {
        Elem.Value = 1;
    }

    TotalSkillPoints = MaxSkillPoints;

    this->Invalidate(EInvalidateWidget::Layout);

    return FReply::Handled();
}

FReply SSkillWidget::OnSaveSkillClicked()
{
	if (OwningHUD.IsValid())
    {
        OwningHUD->SetSavedSkillData(SkillLevels, TotalSkillPoints);
    }
	return FReply::Handled();
}

FReply SSkillWidget::OnSkillClicked(FString SkillName)
{
	SelectedSkillName = SkillName;
    return FReply::Handled();
}
