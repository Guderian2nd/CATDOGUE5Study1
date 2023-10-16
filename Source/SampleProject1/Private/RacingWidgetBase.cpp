// Fill out your copyright notice in the Description page of Project Settings.


#include "RacingWidgetBase.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/CanvasPanel.h"
#include "Misc/Timespan.h"


void URacingWidgetBase::SetArrowLoc_Implementation(bool IsWaypointOutOfScreen, FVector2D WaypointLocation)
{
	if (IsWaypointOutOfScreen)
	{
		double ScreenLocXOverViewportX, ScreenLocXOverViewportY = 0.0;
		auto ArrowPosition = FVector2D{};
		if (IsPointCloserToXAxis(WaypointLocation, ScreenLocXOverViewportX, ScreenLocXOverViewportY))
		{
			USlateBlueprintLibrary::ScreenToViewport(this, (1.0 / ScreenLocXOverViewportX) * WaypointLocation, ArrowPosition);
		}
		else
		{
			USlateBlueprintLibrary::ScreenToViewport(this, (1.0 / ScreenLocXOverViewportY) * WaypointLocation, ArrowPosition);
		}

		if (WaypointIndicatorArrow)
		{
			UWidgetLayoutLibrary::SlotAsCanvasSlot(WaypointIndicatorArrow)->SetPosition(ArrowPosition);

			WaypointIndicatorArrow->SetRenderTransformAngle(FMath::RadiansToDegrees(atan2(WaypointLocation.Y, WaypointLocation.X)) - 270.0);
		}
	}
	else
	{
		auto ArrowPosition = FVector2D{};

		if (WaypointIndicatorArrow)
		{
			USlateBlueprintLibrary::ScreenToViewport(this, WaypointLocation, ArrowPosition);
			UWidgetLayoutLibrary::SlotAsCanvasSlot(WaypointIndicatorArrow)->SetPosition(ArrowPosition);

			WaypointIndicatorArrow->SetRenderTransformAngle(180.0);
		}
	}
}

void URacingWidgetBase::SetArrowVisibility_Implementation(bool IsVisible)
{
	if (WaypointIndicatorArrow)
	{
		WaypointIndicatorArrow->SetVisibility(IsVisible ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Collapsed);
	}
}

void URacingWidgetBase::SetTimerText_Implementation(float TimeInSeconds)
{
	if (TimerTextWidget)
	{
		SetTextTime(TimeInSeconds, TimerTextWidget);
	}
}

void URacingWidgetBase::SetWaypointNum_Implementation(int AcquiredWaypointNum, int TotalWaypointNum)
{
	auto WaypointProgressString = FString::Printf(TEXT("%d / %d"), AcquiredWaypointNum, TotalWaypointNum);

	if (WaypointProgressTextWidget)
	{
		WaypointProgressTextWidget->SetText(FText::FromString(WaypointProgressString));
	}
}

void URacingWidgetBase::ToggleVictoryMessage_Implementation(bool IsRaceFinished, float FinalTime)
{
	if (VictoryCanvasPanel)
	{
		VictoryCanvasPanel->SetVisibility(IsRaceFinished ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
	}
	if (RacingCanvasPanel)
	{
		RacingCanvasPanel->SetVisibility(IsRaceFinished ? ESlateVisibility::Collapsed : ESlateVisibility::Visible);
	}
	if (FinalTimeTextWidget && IsRaceFinished)
	{
		SetTextTime(FinalTime, FinalTimeTextWidget);
	}
}

bool URacingWidgetBase::IsPointCloserToXAxis(FVector2D ScreenLocation, double& ScreenLocXOverViewportX, double& ScreenLocYOverViewportY)
{
	auto ViewportSize = FVector2D{};
	GetWorld()->GetGameViewport()->GetViewportSize(ViewportSize);
	ViewportSize = (ViewportSize / -2.0).GetAbs();

	auto ScreenLocAbsVec = ScreenLocation.GetAbs();

	ScreenLocXOverViewportX = ScreenLocAbsVec.X / ViewportSize.X;
	ScreenLocYOverViewportY = ScreenLocAbsVec.Y / ViewportSize.Y;

	return ScreenLocXOverViewportX > ScreenLocYOverViewportY;
}

void URacingWidgetBase::SetTextTime(double Seconds, UTextBlock* TextToSet)
{
	auto Mins = FMath::FloorToInt(FTimespan::FromSeconds(Seconds).GetTotalMinutes());
	auto Secs = FTimespan::FromSeconds(Seconds).GetSeconds();
	auto MilliSecs = FTimespan::FromSeconds(Seconds).GetFractionMilli();

	TextToSet->SetText(FText::FromString(FString::Printf(TEXT("%02d:%02d.%03d"), Mins, Secs, MilliSecs)));
}
