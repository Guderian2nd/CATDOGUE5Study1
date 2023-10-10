// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "RacingControllerInterface.h"
#include "MyRacingPlayerControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class SAMPLEPROJECT1_API AMyRacingPlayerControllerBase : public APlayerController, public IRacingControllerInterface
{
	GENERATED_BODY()
	
public:
	virtual void SetupInputComponent() override;

	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void UpdateWidget(float DeltaTime);

	void UpdatePawnForceArrow();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Provide Pawn with Info")
	FVector2D GetBodyScreenPos(UStaticMeshComponent* BodyPawn);

#pragma region Interfaces
	FVector2D GetMousePosXYDelta_Implementation() override;

	AWaypointsCourseActor* GetCourse_Implementation() override;
	void OverlappedWaypoint_Implementation(class ARacingWaypointActor* Waypoint) override;
	void SetCourse_Implementation(AWaypointsCourseActor* NewCourse) override;
#pragma endregion


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn")
	/// <summary>
	/// Object reference to Racing pawn. Null when not possessed.
	/// </summary>
	class ARacingPawn* RacingPawn = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn")
	/// <summary>
	/// Object reference to UI Widget. 
	/// </summary>
	class URacingWidgetBase* Widget = nullptr;

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
	TSubclassOf<URacingWidgetBase> UserWidgetClass = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Course Info")
	float RacingTime;

	UPROPERTY(VisibleAnywhere, Category = "Course Info")
	int CurrentWaypointNum;

	UPROPERTY(VisibleAnywhere, Category = "Course Info")

	int TotalWaypointsNum;

	UPROPERTY(VisibleAnywhere, Category = "CourseActor")
	class AWaypointsCourseActor* MyCourse = nullptr;
};
