// Fill out your copyright notice in the Description page of Project Settings.


#include "SMainMenuWidget.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/HUD.h"
#include "MenuHUD.h"

#define LOCTEXT_NAMESPACE "MainMene"

void SMainMenuWidget::Construct(const FArguments& InArgs)
{
	bCanSupportFocus = true;

	OwningHUD = InArgs._OwningHUD;

	const FMargin ContentPadding = FMargin(10.f, 10.f,10.f,10.f);
	const FMargin ButtonPadding = FMargin(20.f);
	const FMargin StatusPadding = FMargin(0.f, 5.f, 0.f, 5.f);

	const FText TitleText = LOCTEXT("GameTitle", "Hong Hye Seong");
	const FText PlayText = LOCTEXT("PlayGame", "A");
	const FText SettingsText = LOCTEXT("Settings", "B");
	const FText QuitText = LOCTEXT("QuitGame", "C");

	FSlateFontInfo ButtonTextStyle = FCoreStyle::Get().GetFontStyle("EmbossedText");
	ButtonTextStyle.Size = 40.f;

	FSlateFontInfo TitleTextStyle = ButtonTextStyle;
	TitleTextStyle.Size = 60.f;

	ChildSlot
		[
			SNew(SOverlay)
			+ SOverlay::Slot()
			.HAlign(HAlign_Right)
			.VAlign(VAlign_Top)
			.Padding(ContentPadding)
			[
				SNew(SHorizontalBox)

				//Play Button
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

				//Play Button
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
						[
							SNew(STextBlock)
							.Font(ButtonTextStyle)
							.Text(SettingsText)
							.Justification(ETextJustify::Center)
						]
					]
				]

				//Play Button
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
			.HAlign(HAlign_Right)
			.VAlign(VAlign_Bottom)
			.Padding(ContentPadding)
			[
				SNew(SHorizontalBox)

				//Play Button
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

				//Play Button
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
						[
							SNew(STextBlock)
							.Font(ButtonTextStyle)
							.Text(SettingsText)
							.Justification(ETextJustify::Center)
						]
					]
				]

				//Play Button
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
					.WidthOverride(1000.f)
					.HeightOverride(30.f)
					[
						SNew(SButton)
						.HAlign(HAlign_Center)
						.VAlign(VAlign_Center) 
						.ButtonColorAndOpacity(FColor::Red)
						[
							SNew(STextBlock)
							.Font(ButtonTextStyle)
							.Text(PlayText)
							.Justification(ETextJustify::Center)
						]
					]
				]

				+ SVerticalBox::Slot()
				.Padding(StatusPadding)
				[
					SNew(SBox)
					.WidthOverride(1000.f)
					.HeightOverride(30.f)
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

#undef LOCTEXT_NAMESPACE