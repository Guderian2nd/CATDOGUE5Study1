// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RacingWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class SAMPLEPROJECT1_API URacingWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Controller Communication")
	void SetArrowLoc(bool IsWaypointOutOfScreen, FVector2D WaypointLocation);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Controller Communication")
	void SetArrowVisibility(bool IsVisible);
	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Controller Communication")
	void SetTimerText(float TimeInSeconds);
	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Controller Communication")
	void SetWaypointNum(int AcquiredWaypointNum, int TotalWaypointNum);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Controller Communication")
	void ToggleVictoryMessage(bool IsRaceFinished, float FinalTime);
};
