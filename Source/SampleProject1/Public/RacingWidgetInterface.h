// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "RacingWidgetInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class URacingWidgetInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SAMPLEPROJECT1_API IRacingWidgetInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Controller Communication")
	void SetArrowLoc(bool IsWaypointOutOfScreen, FVector2D WaypointLocation);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Controller Communication")
	void SetArrowVisibility(bool IsVisible);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Controller Communication")
	void SetTimerText(float TimeInSeconds);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Controller Communication")
	void SetWaypointNum(int AcquiredWaypointNum, int TotalWaypointNum);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Controller Communication")
	void ToggleVictoryMessage(bool IsRaceFinished, float FinalTime);
};
