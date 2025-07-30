// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MenuHUD.generated.h"

/**
 * 
 */
UCLASS()
class MOBILEPROJECT_API AMenuHUD : public AHUD
{
	GENERATED_BODY()
	
protected:
	TSharedPtr<class SMainMenuWidget> MenuWidget;
	TSharedPtr<class SWidget> MenuWidgetContainer;
	TSharedPtr<class SInventoryWidget> InventoryWidget;
	TSharedPtr<class SSkillWidget> SkillWidget;
	virtual void BeginPlay() override;

public:

	TMap<FString, int32> SavedSkillLevels;
	int32 SavedTotalSkillPoints = 0;

	void ShowMenu();
	void RemoveMenu();
	void ShowInventory();
	void ShowSkill();
	void CloseSkillWidget();
	void CloseInvenWidget();
	void SetSavedSkillData(const TMap<FString, int32>& Levels, int32 Points);
};