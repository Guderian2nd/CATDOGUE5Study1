// Fill out your copyright notice in the Description page of Project Settings.


#include "MyRacingPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

void AMyRacingPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (auto* EnhancedInputComp = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComp->BindAction(AccelerateAction, ETriggerEvent::Triggered, this, &AMyRacingPlayerController::Accelerate);
		EnhancedInputComp->BindAction(CameraTurnAction, ETriggerEvent::Triggered, this, &AMyRacingPlayerController::CameraTurn);
		EnhancedInputComp->BindAction(CameraZoomAction, ETriggerEvent::Triggered, this, &AMyRacingPlayerController::CameraZoon);
		EnhancedInputComp->BindActionValue(MouseMovementAction);

	}
}

void AMyRacingPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	auto* EnhancedInputComponentSubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (EnhancedInputComponentSubSystem && InputContext)
	{
		EnhancedInputComponentSubSystem->AddMappingContext(InputContext, 0);
	}

	//RacingPawn = Cast<ARacingPawn>(InPawn);
}

void AMyRacingPlayerController::OnUnPossess()
{
	Super::OnUnPossess();

	//RacingPawn = nullptr;
}

void AMyRacingPlayerController::Accelerate(const FInputActionValue& Value)
{
}

void AMyRacingPlayerController::CameraTurn(const FInputActionValue& Value)
{
}

void AMyRacingPlayerController::CameraZoon(const FInputActionValue& Value)
{
}
