// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "MyRacingPlayerControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class SAMPLEPROJECT1_API AMyRacingPlayerControllerBase : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void SetupInputComponent() override;

	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Provide Pawn with Info")
	FVector2D GetBodyScreenPos(UStaticMeshComponent* BodyPawn);

	UFUNCTION(BlueprintCallable, Category = "Provide Pawn with Info")
	FVector2D GetMousePosXYDelta();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn")
	/// <summary>
	/// Object reference to Racing pawn. Null when not possessed.
	/// </summary>
	class ARacingPawn* RacingPawn = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn")
	/// <summary>
	/// Object reference to UI Widget. 
	/// </summary>
	class UUserWidget* Widget = nullptr;

private:
	UFUNCTION(BlueprintCallable, Category = "Inputs to Pawn")
	void Accelerate(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, Category = "Inputs to Pawn")
	void CameraTurn(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, Category = "Inputs to Pawn")
	void CameraZoom(const FInputActionValue& Value);

	//UFUNCTION(BlueprintCallable, Category = "Inputs to Pawn")
	//void MouseMovement(const FInputActionValue& Value);

	UPROPERTY(EditAnywhere, Category = "Enhanced Input")
	/// <summary>
	/// Input Mapping Context for this Player Controller
	/// </summary>
	class UInputMappingContext* InputContext;

	UPROPERTY(VisibleAnywhere, Category = "Enhanced Input")
	class UEnhancedInputComponent* EnhancedInputComp;

	UPROPERTY(EditAnywhere, Category = "Enhanced Input")
	class UInputAction* AccelerateAction;

	UPROPERTY(EditAnywhere, Category = "Enhanced Input")
	UInputAction* CameraTurnAction;

	UPROPERTY(EditAnywhere, Category = "Enhanced Input")
	UInputAction* CameraZoomAction;

	UPROPERTY(EditAnywhere, Category = "Enhanced Input")
	UInputAction* MouseMovementAction;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> UserWidgetClass = nullptr;
};
