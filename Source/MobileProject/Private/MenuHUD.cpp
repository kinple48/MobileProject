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
#include "SOptionWidget.h"

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
    if (!InventoryWidget.IsValid())
    {
        InventoryWidget = SNew(SInventoryWidget);
        GEngine->GameViewport->AddViewportWidgetContent(InventoryWidget.ToSharedRef());
    }
}

void AMenuHUD::ShowSkill()
{
	if (!SkillWidget.IsValid())
    {
        SkillWidget = SNew(SSkillWidget);
        GEngine->GameViewport->AddViewportWidgetContent(SkillWidget.ToSharedRef());
    }
}

void AMenuHUD::ShowOption()
{
	if (!OptionWidget.IsValid())
    {
        OptionWidget = SNew(SOptionWidget);
        GEngine->GameViewport->AddViewportWidgetContent(OptionWidget.ToSharedRef());
    }
}