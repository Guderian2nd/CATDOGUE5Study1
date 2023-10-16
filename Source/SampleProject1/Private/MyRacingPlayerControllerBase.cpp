// Fill out your copyright notice in the Description page of Project Settings.


#include "MyRacingPlayerControllerBase.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Logging/StructuredLog.h"
#include "RacingPawn.h"
#include "Kismet/GameplayStatics.h"
#include "RacingWidgetBase.h"
#include "WaypointsCourseActor.h"
#include "RacingWaypointActor.h"
#include "Blueprint/WidgetLayoutLibrary.h"

void AMyRacingPlayerControllerBase::SetupInputComponent()
{
	Super::SetupInputComponent();

	EnhancedInputComp = Cast<UEnhancedInputComponent>(InputComponent);

	if (EnhancedInputComp)
	{
		EnhancedInputComp->BindAction(AccelerateAction, ETriggerEvent::Triggered, this, &AMyRacingPlayerControllerBase::Accelerate);
		EnhancedInputComp->BindAction(AccelerateAction, ETriggerEvent::Completed, this, &AMyRacingPlayerControllerBase::Accelerate);

		EnhancedInputComp->BindAction(CameraTurnAction, ETriggerEvent::Triggered, this, &AMyRacingPlayerControllerBase::CameraTurn);
		EnhancedInputComp->BindAction(CameraTurnAction, ETriggerEvent::Completed, this, &AMyRacingPlayerControllerBase::CameraTurn);

		EnhancedInputComp->BindAction(CameraZoomAction, ETriggerEvent::Triggered, this, &AMyRacingPlayerControllerBase::CameraZoom);
	
		EnhancedInputComp->BindActionValue(MouseMovementAction);
	}
}

void AMyRacingPlayerControllerBase::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	auto* EnhancedInputComponentSubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (EnhancedInputComponentSubSystem && InputContext)
	{
		EnhancedInputComponentSubSystem->AddMappingContext(InputContext, 0);
	}

	RacingPawn = Cast<ARacingPawn>(InPawn);

	SetInputMode(FInputModeGameAndUI().SetHideCursorDuringCapture(false));
}

void AMyRacingPlayerControllerBase::OnUnPossess()
{
	Super::OnUnPossess();

	RacingPawn = nullptr;
}

void AMyRacingPlayerControllerBase::Tick(float DeltaTime)
{
	UpdatePawnForceArrow();

	UpdateWidget(DeltaTime);
}

void AMyRacingPlayerControllerBase::UpdateWidget(float DeltaTime)
{
	if (CurrentWaypointNum < TotalWaypointsNum)
	{
		RacingTime += DeltaTime;

		if (Widget)
		{
			IRacingWidgetInterface::Execute_SetTimerText(Widget, RacingTime);

			FVector2D WaypointViewportCoord = {};
			if (CurrentWaypointNum < TotalWaypointsNum)
			{
				FVector2D ViewPortSizeVec = {};
				GetLocalPlayer()->ViewportClient->GetViewportSize(ViewPortSizeVec);

				bool IsWaypointOutOfScreen = true;

				if (ProjectWorldLocationToScreen(MyCourse->GetWaypoint(CurrentWaypointNum)->GetActorLocation(), WaypointViewportCoord, true))
				{
					IsWaypointOutOfScreen = !(WaypointViewportCoord.ComponentwiseAllGreaterOrEqual(FVector2D::ZeroVector) && WaypointViewportCoord.ComponentwiseAllLessOrEqual(ViewPortSizeVec));
				}
				else
				{
					FVector CameraLoc = {};
					FRotator CameraRot = {};
					GetPlayerViewPoint(CameraLoc, CameraRot);

					FTransform CameraTransform = FTransform(CameraRot, CameraLoc, FVector(1, 1, 1));

					auto WaypointEyeCoordLocation = CameraTransform.InverseTransformPositionNoScale(MyCourse->GetWaypoint(CurrentWaypointNum)->GetActorLocation());

					WaypointEyeCoordLocation.X = -WaypointEyeCoordLocation.X;

					auto NewWaypointWorldLoc = CameraTransform.TransformPositionNoScale(WaypointEyeCoordLocation);

					ProjectWorldLocationToScreen(NewWaypointWorldLoc, WaypointViewportCoord, true);
				}

				auto CenteredCoord = WaypointViewportCoord - ViewPortSizeVec / 2;

				UE_LOG(LogTemp, Warning, TEXT("%s"), *CenteredCoord.ToString());

				IRacingWidgetInterface::Execute_SetArrowLoc(Widget, IsWaypointOutOfScreen, CenteredCoord);
			}
		}
	}
}

void AMyRacingPlayerControllerBase::UpdatePawnForceArrow()
{
	if (RacingPawn)
	{
		float MouseX, MouseY = 0.0f;
		GetMousePosition(MouseX, MouseY);
		FVector2D ViewPortSizeVec = { 0, 0 };

		GetLocalPlayer()->ViewportClient->GetViewportSize(ViewPortSizeVec);

		RacingPawn->SetBodyScreenPos(GetBodyScreenPos(RacingPawn->PawnBody));
		RacingPawn->SetAccelerateVector(FVector2D(MouseX, ViewPortSizeVec.Y - MouseY));
	}
}

void AMyRacingPlayerControllerBase::BeginPlay()
{
	Super::BeginPlay();

	RacingTime = 0.0f;
}

FVector2D AMyRacingPlayerControllerBase::GetBodyScreenPos(UStaticMeshComponent* BodyPawn)
{
	FVector2D ScreenPos = { };
	auto tmp = BodyPawn->GetComponentLocation();
	ProjectWorldLocationToScreen(tmp, ScreenPos, true);

	FVector2D ViewPortSizeVec = { };
	GetLocalPlayer()->ViewportClient->GetViewportSize(ViewPortSizeVec);

	return FVector2D(ScreenPos.X, ViewPortSizeVec.Y - ScreenPos.Y);
}

FVector2D AMyRacingPlayerControllerBase::GetMousePosXYDelta_Implementation()
{
	return EnhancedInputComp->GetBoundActionValue(MouseMovementAction).Get<FVector2D>();
}

AWaypointsCourseActor* AMyRacingPlayerControllerBase::GetCourse_Implementation()
{
	return MyCourse;
}

void AMyRacingPlayerControllerBase::OverlappedWaypoint_Implementation(ARacingWaypointActor* Waypoint)
{
	if (MyCourse->IsOverlappedWaypointValid(Waypoint, CurrentWaypointNum))
	{
		CurrentWaypointNum++;
		if (Widget)
		{
			IRacingWidgetInterface::Execute_SetWaypointNum(Widget, CurrentWaypointNum, TotalWaypointsNum);
		}
		if (CurrentWaypointNum == TotalWaypointsNum)
		{
			IRacingWidgetInterface::Execute_SetArrowVisibility(Widget, false);
			IRacingWidgetInterface::Execute_ToggleVictoryMessage(Widget, true, RacingTime);
		}
	}
}

void AMyRacingPlayerControllerBase::SetCourse_Implementation(AWaypointsCourseActor* NewCourse)
{
	MyCourse = NewCourse;
	CurrentWaypointNum = 0;
	TotalWaypointsNum = MyCourse->GetTotalWaypointsNum();

	if (UserWidgetClass)
	{
		Widget = CreateWidget(this, UserWidgetClass, "RacingWidget");
		if (Widget)
		{
			Widget->AddToViewport();

			IRacingWidgetInterface::Execute_SetArrowVisibility(Widget, true);
			IRacingWidgetInterface::Execute_SetWaypointNum(Widget, CurrentWaypointNum, TotalWaypointsNum);
			IRacingWidgetInterface::Execute_ToggleVictoryMessage(Widget, false, 0.0f);
		}
	}
}

void AMyRacingPlayerControllerBase::Accelerate(const FInputActionValue& Value)
{
	auto IsAccelerating = Value.Get<bool>();
	RacingPawn->AcceleratePawn(IsAccelerating);
}

void AMyRacingPlayerControllerBase::CameraTurn(const FInputActionValue& Value)
{
	auto IsTurning = Value.Get<bool>();
	RacingPawn->TurnPawnCamera(IsTurning);
}

void AMyRacingPlayerControllerBase::CameraZoom(const FInputActionValue& Value)
{
	RacingPawn->ZoomPawnCamera(Value.GetMagnitude());
}
