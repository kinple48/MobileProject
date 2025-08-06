#include "SMainMenuWidget.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/HUD.h"
#include "MenuHUD.h"
#include "../MobileProjectCharacter.h"

void SMainMenuWidget::Construct(const FArguments& InArgs)
{
	bCanSupportFocus = true;

	OwningHUD = InArgs._OwningHUD;
	OwnerCharacter = InArgs._OwnerCharacter;

	const FMargin ContentPadding = FMargin(10.f);
	const FMargin ButtonPadding = FMargin(1.f);
	const FMargin StatusPadding = FMargin(0.f, 5.f, 0.f, 5.f);

	const FString PlayText = TEXT("A");
	const FString SettingsText = TEXT("B");
	const FString QuitText = TEXT("C");

	FSlateFontInfo ButtonTextStyle = FCoreStyle::Get().GetFontStyle("EmbossedText");
	ButtonTextStyle.Size = 40.f;

	FSlateFontInfo TitleTextStyle = ButtonTextStyle;
	TitleTextStyle.Size = 60.f;

	
	if (UTexture2D* InvenTex = LoadObject<UTexture2D>(nullptr, TEXT("/Game/TopDown/Image/inventory.inventory")))
	{
		InvenButtonBrush.SetResourceObject(InvenTex);
		InvenButtonBrush.ImageSize = FVector2D(100, 100);
	}

	if (UTexture2D* SkillTex = LoadObject<UTexture2D>(nullptr, TEXT("/Game/TopDown/Image/skills.skills")))
	{
		SkillButtonBrush.SetResourceObject(SkillTex);
		SkillButtonBrush.ImageSize = FVector2D(100, 100);
	}

	if (UTexture2D* QuickSlotTex = LoadObject<UTexture2D>(nullptr, TEXT("/Game/TopDown/Image/base.base")))
	{
		QuickSlotBrush.SetResourceObject(QuickSlotTex);
		QuickSlotBrush.ImageSize = FVector2D(200, 200);
	}

	if (UTexture2D* ASkillTex = LoadObject<UTexture2D>(nullptr, TEXT("/Game/TopDown/Image/A.A")))
	{
		ASkillBrush.SetResourceObject(ASkillTex);
		ASkillBrush.ImageSize = FVector2D(200, 200);
	}

	if (UTexture2D* BSkillTex = LoadObject<UTexture2D>(nullptr, TEXT("/Game/TopDown/Image/B.B")))
	{
		BSkillBrush.SetResourceObject(BSkillTex);
		BSkillBrush.ImageSize = FVector2D(200, 200);
	}

	if (UTexture2D* CSkillTex = LoadObject<UTexture2D>(nullptr, TEXT("/Game/TopDown/Image/C.C")))
	{
		CSkillBrush.SetResourceObject(CSkillTex);
		CSkillBrush.ImageSize = FVector2D(200, 200);
	}

	ChildSlot
		[
			SNew(SOverlay)
			+ SOverlay::Slot()
			.HAlign(HAlign_Right)
			.VAlign(VAlign_Top)
			.Padding(ContentPadding)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(ButtonPadding)
				[
					SNew(SBox)
					.WidthOverride(120.f)
					.HeightOverride(120.f)
					[
						SNew(SButton)
						.OnClicked(this, &SMainMenuWidget::OnInvenClicked)
						.ButtonStyle(FCoreStyle::Get(), "NoBorder")
						.ContentPadding(0)                          
						.HAlign(HAlign_Fill)
						.VAlign(VAlign_Fill)
						[
							SNew(SImage)
							.Image(&InvenButtonBrush)
						]
					]
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(ButtonPadding)
				[
					SNew(SBox)
					.WidthOverride(120.f)
					.HeightOverride(120.f)
					[
						SNew(SButton)
						.OnClicked(this, &SMainMenuWidget::OnSkillClicked)
						.ButtonStyle(FCoreStyle::Get(), "NoBorder")
						.ContentPadding(0)                       
						.HAlign(HAlign_Fill)
						.VAlign(VAlign_Fill)
						[
							SNew(SImage)
							.Image(&SkillButtonBrush)
						]
					]
				]
			]
			+ SOverlay::Slot()
			.HAlign(HAlign_Right)
			.VAlign(VAlign_Bottom)
			.Padding(ContentPadding)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(ButtonPadding)
				[
					SNew(SButton)
					.OnClicked(this, &SMainMenuWidget::OnASkillClicked)
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.ButtonStyle(FCoreStyle::Get(), "NoBorder")
					[
						SNew(SImage)
						.Image(&ASkillBrush)
					]
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(ButtonPadding)
				[
					
					SNew(SButton)
					.OnClicked(this, &SMainMenuWidget::OnBSkillClicked)
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.ButtonStyle(FCoreStyle::Get(), "NoBorder")
					[
						SNew(SImage)
						.Image(&BSkillBrush)
					]
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(ButtonPadding)
				[
					SNew(SButton)
					.OnClicked(this, &SMainMenuWidget::OnBSkillClicked)
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.ButtonStyle(FCoreStyle::Get(), "NoBorder")
					[
						SNew(SImage)
						.Image(&CSkillBrush)
					]
				]
			]
			+ SOverlay::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Bottom)
			.Padding(ContentPadding)
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.Padding(StatusPadding)
				[
					SNew(SBox)
					.WidthOverride(500.f)
					.HeightOverride(30.f)
					[
						SNew(SProgressBar)
						.Percent(1.f)
						.FillColorAndOpacity(FLinearColor(300.f, 0.f, 0.f, 1.f))
					]
				]

				+ SVerticalBox::Slot()
				.Padding(StatusPadding)
				[
					SNew(SBox)
					.WidthOverride(500.f)
					.HeightOverride(30.f)
					[
						SNew(SProgressBar)
						.Percent_Lambda([this]() -> float
						{
							if (OwnerCharacter.IsValid() && OwnerCharacter->MaxMP > 0.f)
							{
								return OwnerCharacter->CurrentMP / OwnerCharacter->MaxMP;
							}
							return 0.f;
						})
					]
				]
			]

		];
}

FReply SMainMenuWidget::OnInvenClicked() const
{
	
	if (OwningHUD.IsValid())
    {
        OwningHUD->ShowInventory();
    }
    return FReply::Handled();
}

FReply SMainMenuWidget::OnSkillClicked() const
{
	if (OwningHUD.IsValid())
    {
        OwningHUD->ShowSkill();
    }
	return FReply::Handled();
}

FReply SMainMenuWidget::OnASkillClicked() const
{
	if (OwnerCharacter.IsValid())
    {
        float SkillAMPCost = 0.2f;
        if (OwnerCharacter->CurrentMP >= SkillAMPCost)
        {
            OwnerCharacter->CurrentMP -= SkillAMPCost;
            OwnerCharacter->CurrentMP = FMath::Clamp(OwnerCharacter->CurrentMP, 0.f, OwnerCharacter->MaxMP);
        }
    }
    return FReply::Handled();
}

FReply SMainMenuWidget::OnBSkillClicked() const
{
	if (OwnerCharacter.IsValid())
    {
        float SkillBMPCost = 0.4f;
        if (OwnerCharacter->CurrentMP >= SkillBMPCost)
        {
            OwnerCharacter->CurrentMP -= SkillBMPCost;
            OwnerCharacter->CurrentMP = FMath::Clamp(OwnerCharacter->CurrentMP, 0.f, OwnerCharacter->MaxMP);
        }
    }
    return FReply::Handled();
}

FReply SMainMenuWidget::OnCSkillClicked() const
{
	if (OwnerCharacter.IsValid())
    {
        float SkillCMPCost = 0.6f;
        if (OwnerCharacter->CurrentMP >= SkillCMPCost)
        {
            OwnerCharacter->CurrentMP -= SkillCMPCost;
            OwnerCharacter->CurrentMP = FMath::Clamp(OwnerCharacter->CurrentMP, 0.f, OwnerCharacter->MaxMP);
        }
    }
    return FReply::Handled();
}
