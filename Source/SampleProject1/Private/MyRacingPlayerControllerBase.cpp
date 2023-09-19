// Fill out your copyright notice in the Description page of Project Settings.


#include "MyRacingPlayerControllerBase.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Logging/StructuredLog.h"
#include "RacingPawn.h"
#include "Kismet/GameplayStatics.h"



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
	if (RacingPawn)
	{
		float MouseX, MouseY = 0.0f;
		GetMousePosition(MouseX, MouseY);
		FVector2D ViewPortSizeVec = { 0, 0 };
		GetLocalPlayer()->ViewportClient->GetViewportSize(ViewPortSizeVec);
		RacingPawn->SetAccelerateVector(FVector2D(MouseX, ViewPortSizeVec.Y - MouseY));
		
		RacingPawn->SetBodyScreenPos(GetBodyScreenPos(RacingPawn->PawnBody));
	}
}

FVector2D AMyRacingPlayerControllerBase::GetBodyScreenPos(UStaticMeshComponent* BodyPawn)
{
	FVector2D ScreenPos = { 0, 0 };
	auto tmp = BodyPawn->GetComponentLocation();
	ProjectWorldLocationToScreen(tmp, ScreenPos);

	FVector2D ViewPortSizeVec = { 0, 0 };
	GetLocalPlayer()->ViewportClient->GetViewportSize(ViewPortSizeVec);

	return FVector2D(ScreenPos.X, ViewPortSizeVec.Y - ScreenPos.Y);
}

FVector2D AMyRacingPlayerControllerBase::GetMousePosXYDelta()
{
	return EnhancedInputComp->GetBoundActionValue(MouseMovementAction).Get<FVector2D>();
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

void AMyRacingPlayerControllerBase::log()
{

}
