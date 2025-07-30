// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuHUD.h"
#include "SMainMenuWidget.h"
#include "Widgets/SWeakWidget.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/HUD.h"
#include "../MobileProjectCharacter.h"
#include "SInventoryWidget.h"
#include "SSkillWidget.h"

void AMenuHUD::BeginPlay()
{
	Super::BeginPlay();
	ShowMenu();
}

void AMenuHUD::ShowMenu()
{
	if (GEngine && GEngine->GameViewport)
	{
		AMobileProjectCharacter* MyCharacter = nullptr;
        if (PlayerOwner)
        {
            MyCharacter = Cast<AMobileProjectCharacter>(PlayerOwner->GetPawn());
        }

		MenuWidget = SNew(SMainMenuWidget).OwningHUD(this).OwnerCharacter(MyCharacter);
		GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(MenuWidgetContainer,SWeakWidget).PossiblyNullContent(MenuWidget.ToSharedRef()));

		if (PlayerOwner)
		{
			PlayerOwner->bShowMouseCursor = true;
		}
	}
}

void AMenuHUD::RemoveMenu()
{
	if (GEngine && GEngine->GameViewport && MenuWidgetContainer.IsValid())
	{
		GEngine->GameViewport->RemoveViewportWidgetContent(MenuWidgetContainer.ToSharedRef());

		if (PlayerOwner)
		{
			PlayerOwner->bShowMouseCursor = false;
			PlayerOwner->SetInputMode(FInputModeGameOnly());
		}
	}
}

void AMenuHUD::ShowInventory()
{
	FInputModeUIOnly InputMode;
	PlayerOwner->SetInputMode(InputMode);
    if (!InventoryWidget.IsValid())
    {
        InventoryWidget = SNew(SInventoryWidget).OwningHUD(this);
        GEngine->GameViewport->AddViewportWidgetContent(InventoryWidget.ToSharedRef(),100);
    }
}

void AMenuHUD::ShowSkill()
{
	FInputModeUIOnly InputMode;
	PlayerOwner->SetInputMode(InputMode);
	if (!SkillWidget.IsValid())
    {
        SkillWidget = SNew(SSkillWidget).OwningHUD(this);
        GEngine->GameViewport->AddViewportWidgetContent(SkillWidget.ToSharedRef(),100);
    }
}

void AMenuHUD::CloseSkillWidget()
{
    if (SkillWidget.IsValid())
    {
        GEngine->GameViewport->RemoveViewportWidgetContent(SkillWidget.ToSharedRef());
        SkillWidget.Reset();
        APlayerController* PC = Cast<APlayerController>(PlayerOwner);
        if (PC)
        {
            PC->SetInputMode(FInputModeGameOnly());
        }
    }
}

void AMenuHUD::CloseInvenWidget()
{
	if (InventoryWidget.IsValid())
    {
        GEngine->GameViewport->RemoveViewportWidgetContent(InventoryWidget.ToSharedRef());
        InventoryWidget.Reset();
        APlayerController* PC = Cast<APlayerController>(PlayerOwner);
        if (PC)
        {
            PC->SetInputMode(FInputModeGameOnly());
        }
    }
}

void AMenuHUD::SetSavedSkillData(const TMap<FString, int32>& Levels, int32 Points)
{
    SavedSkillLevels = Levels;
    SavedTotalSkillPoints = Points;
}
