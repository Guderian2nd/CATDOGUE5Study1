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
	virtual void SetArrowLoc_Implementation(bool IsWaypointOutOfScreen, FVector2D WaypointLocation);

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

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parent Class Properties")
	/// <summary>
	/// The arrow that points to on or off screen waypoints
	/// </summary>
	UWidget* WaypointIndicatorArrow = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parent Class Properties")
	/// <summary>
	/// Text that displays the current time elapsed since start of race
	/// </summary>
	class UTextBlock* TimerTextWidget = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parent Class Properties")
	/// <summary>
	/// Text that displays the final record after finishing the race
	/// </summary>
	UTextBlock* FinalTimeTextWidget = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parent Class Properties")
	/// <summary>
	/// Text Widget that displays how much of the race course you've run
	/// </summary>
	UTextBlock* WaypointProgressTextWidget = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parent Class Properties")
	/// <summary>
	/// Panel that holds information about the ongoing race
	/// </summary>
	class UCanvasPanel* RacingCanvasPanel = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parent Class Properties")
	/// <summary>
	/// Panel that displays when race is finished
	/// </summary>
	UCanvasPanel* VictoryCanvasPanel = nullptr;

private:
	/// <summary>
	/// Checks whether an arrow from screen center to an out-of-screen location touches the sides or top/bottom of the screen
	/// </summary>
	/// <param name="ScreenLocation"></param>
	/// <param name="ScreenLocXOverViewportX">Writes the ScreenLocX/ViewportX value to this variable</param>
	/// <param name="ScreenLocYOverViewportY">Writes the ScreenLocY/ViewportY value to this variable</param>
	/// <returns>True if the line from screen center to ScreenLocation touches the sides, false if it touches the top or bottom of the screen edge</returns>
	bool IsPointCloserToXAxis(FVector2D ScreenLocation, double& ScreenLocXOverViewportX, double& ScreenLocYOverViewportY);

	/// <summary>
	/// Sets the text of a UTextBlock in mm:ss.xxx time format when given a time in seconds.
	/// </summary>
	/// <param name="Seconds"></param>
	/// <param name="TextToSet"></param>
	void SetTextTime(double Seconds, UTextBlock* TextToSet);
};
