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
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Controller Communication")
	void SetArrowLoc(bool IsWaypointOutOfScreen, FVector2D WaypointLocation);
	virtual void SetArrowLoc_Implementation(bool IsWaypointOutOfScreen, FVector2D MouseScreenPos);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Controller Communication")
	void SetArrowVisibility(bool IsVisible);
	virtual void SetArrowVisibility_Implementation(bool IsVisible);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Controller Communication")
	void SetTimerText(float TimeInSeconds);
	virtual void SetTimerText_Implementation(float TimeInSeconds);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Controller Communication")
	void SetWaypointNum(int AcquiredWaypointNum, int TotalWaypointNum);
	virtual void SetWaypointNum_Implementation(int AcquiredWaypointNum, int TotalWaypointNum);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Controller Communication")
	void ToggleVictoryMessage(bool IsRaceFinished, float FinalTime);
	virtual void ToggleVictoryMessage_Implementation(bool IsRaceFinished, float FinalTime);
};
