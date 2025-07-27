// Fill out your copyright notice in the Description page of Project Settings.


#include "SMainMenuWidget.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/HUD.h"
#include "MenuHUD.h"
#include "../MobileProjectCharacter.h"
#define LOCTEXT_NAMESPACE "MainMene"

void SMainMenuWidget::Construct(const FArguments& InArgs)
{
	bCanSupportFocus = true;

	OwningHUD = InArgs._OwningHUD;
	OwnerCharacter = InArgs._OwnerCharacter;

	const FMargin ContentPadding = FMargin(10.f);
	const FMargin ButtonPadding = FMargin(5.f);
	const FMargin StatusPadding = FMargin(0.f, 5.f, 0.f, 5.f);

	const FText PlayText = LOCTEXT("A skill", "A");
	const FText SettingsText = LOCTEXT("B skill", "B");
	const FText QuitText = LOCTEXT("C skill", "C");

	FSlateFontInfo ButtonTextStyle = FCoreStyle::Get().GetFontStyle("EmbossedText");
	ButtonTextStyle.Size = 40.f;

	FSlateFontInfo TitleTextStyle = ButtonTextStyle;
	TitleTextStyle.Size = 60.f;

	
	if (UTexture2D* InvenTex = LoadObject<UTexture2D>(nullptr, TEXT("/Game/TopDown/Image/inventory.inventory")))
	{
		InvenButtonBrush.SetResourceObject(InvenTex);
		InvenButtonBrush.ImageSize = FVector2D(100, 100);
	}

	if (UTexture2D* SettingsTex = LoadObject<UTexture2D>(nullptr, TEXT("/Game/TopDown/Image/options.options")))
	{
		SettingsButtonBrush.SetResourceObject(SettingsTex);
		SettingsButtonBrush.ImageSize = FVector2D(100, 100);
	}

	if (UTexture2D* SkillTex = LoadObject<UTexture2D>(nullptr, TEXT("/Game/TopDown/Image/skills.skills")))
	{
		SkillButtonBrush.SetResourceObject(SkillTex);
		SkillButtonBrush.ImageSize = FVector2D(100, 100);
	}

	ChildSlot
		[
			SNew(SOverlay)
			.Visibility(EVisibility::HitTestInvisible)
			+ SOverlay::Slot()
			.HAlign(HAlign_Right)
			.VAlign(VAlign_Top)
			.Padding(ContentPadding)
			[
				SNew(SHorizontalBox)

				//Inventory
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
						.ButtonStyle(FCoreStyle::Get(), "NoBorder") // 선택: 버튼 테두리 없애기
						.ContentPadding(0)                          // 여백 제거
						.HAlign(HAlign_Fill)
						.VAlign(VAlign_Fill)
						[
							SNew(SImage)
							.Image(&InvenButtonBrush)
						]
					]
				]

				//Skill
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

				//Option
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(ButtonPadding)
				[
					SNew(SBox)
					.WidthOverride(120.f)
					.HeightOverride(120.f)
					[
						SNew(SButton)
						.OnClicked(this, &SMainMenuWidget::OnOptionClicked)
						.ButtonStyle(FCoreStyle::Get(), "NoBorder")
						.ContentPadding(0)                          
						.HAlign(HAlign_Fill)
						.VAlign(VAlign_Fill) 
						[
							SNew(SImage)
							.Image(&SettingsButtonBrush)
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

				// A Skill
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(ButtonPadding)
				[
					SNew(SBox)
					.WidthOverride(100.f)
					.HeightOverride(100.f)
					[
						SNew(SButton)
						.HAlign(HAlign_Center)
						.VAlign(VAlign_Center) 
						.ButtonColorAndOpacity(FColor::Magenta)
						[
							SNew(STextBlock)
							.Font(ButtonTextStyle)
							.Text(PlayText)
							.Justification(ETextJustify::Center)
						]
					]
				]

				// B Skill
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(ButtonPadding)
				[
					SNew(SBox)
					.WidthOverride(100.f)
					.HeightOverride(100.f)
					[
						SNew(SButton)
						.HAlign(HAlign_Center)
						.VAlign(VAlign_Center) 
						.ButtonColorAndOpacity(FColor::Blue)
						[
							SNew(STextBlock)
							.Font(ButtonTextStyle)
							.Text(SettingsText)
							.Justification(ETextJustify::Center)
						]
					]
				]

				// C Skill
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(ButtonPadding)
				[
					SNew(SBox)
					.WidthOverride(100.f)
					.HeightOverride(100.f)
					[
						SNew(SButton)
						.HAlign(HAlign_Center)
						.VAlign(VAlign_Center) 
						.ButtonColorAndOpacity(FColor::Green)
						[
							SNew(STextBlock)
							.Font(ButtonTextStyle)
							.Text(QuitText)
							.Justification(ETextJustify::Center)
						]
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
							return 0.5f;
						})
					]
				]
			]

		];
}

FReply SMainMenuWidget::OnPlayClicked() const
{
	if (OwningHUD.IsValid())
	{
		OwningHUD->RemoveMenu();
	}

	return FReply::Handled();
}

FReply SMainMenuWidget::OnQuitClicked() const
{
	if (OwningHUD.IsValid())
	{
		if (APlayerController* PC = OwningHUD->PlayerOwner)
		{
			PC->ConsoleCommand("quit");
		}
	}

	return FReply::Handled();
}

FReply SMainMenuWidget::OnInvenClicked() const
{
	GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Red, TEXT("Hello, Debug World!"));
	if (OwningHUD.IsValid())
    {
        OwningHUD->ShowInventory();
    }
    return FReply::Handled();
}

FReply SMainMenuWidget::OnSkillClicked() const
{
	return FReply::Handled();
}

FReply SMainMenuWidget::OnOptionClicked() const
{
	return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE