// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "MyRacingPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class ARacingPawn;
/**
 * 
 */
UCLASS()
class SAMPLEPROJECT1_API AMyRacingPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void SetupInputComponent() override;

	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

	/**
	UPROPERTY(EditAnywhere, BluepringReadWrite, Category = "Pawn")
	/// <summary>
	/// Object reference to Racing pawn. Null when not possessed.
	/// </summary>
	ARacingPawn* RacingPawn = nullptr;
	//*/

private:
	UFUNCTION(BlueprintCallable, Category = "Inputs to Pawn")
	void Accelerate(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, Category = "Inputs to Pawn")
	void CameraTurn(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, Category = "Inputs to Pawn")
	void CameraZoon(const FInputActionValue& Value);

	//UFUNCTION(BlueprintCallable, Category = "Inputs to Pawn")
	//void MouseMovement(const FInputActionValue& Value);

	UPROPERTY(EditAnywhere, Category = "Enhanced Input")
	/// <summary>
	/// Input Mapping Context for this Player Controller
	/// </summary>
	class UInputMappingContext* InputContext;

	UPROPERTY(VisibleAnywhere, Category = "Enhanced Input")
	class UInputAction* AccelerateAction;

	UPROPERTY(VisibleAnywhere, Category = "Enhanced Input")
	class UInputAction* CameraTurnAction;

	UPROPERTY(VisibleAnywhere, Category = "Enhanced Input")
	class UInputAction* CameraZoomAction;

	UPROPERTY(VisibleAnywhere, Category = "Enhanced Input")
	class UInputAction* MouseMovementAction;

	FVector2D MouseScreenPosXY = { 0, 0 };


};
