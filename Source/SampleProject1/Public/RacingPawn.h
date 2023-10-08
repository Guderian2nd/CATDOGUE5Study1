// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "RacingPawnInterface.h"
#include "RacingPawn.generated.h"

UCLASS()
class SAMPLEPROJECT1_API ARacingPawn : public APawn, public IRacingPawnInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ARacingPawn();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Pawn Movement")
	void AcceleratePawn(bool TurnOnAcceleration);
	virtual void AcceleratePawn_Implementation(bool TurnOnAcceleration);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Arrow Movement")
	void SetAccelerateVector(FVector2D MouseScreenPos);
	virtual void SetAccelerateVector_Implementation(FVector2D MouseScreenPos);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Arrow Movement")
	void SetArrowColor(bool ArrowActive);


	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Camera Movement")
	void TurnPawnCamera(bool IsCameraTurningOn);
	virtual void TurnPawnCamera_Implementation(bool IsCameraTurningOn);


	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Camera Movement")
	void ZoomPawnCamera(float DeltaZoomValue);
	virtual void ZoomPawnCamera_Implementation(float DeltaZoomValue);

	UFUNCTION(BlueprintCallable, Category = "Initialization")
	void ComponentsInitializeBP(
		USceneComponent* RootComp, 
		UCameraComponent* PawnCameraComp, 
		USpringArmComponent* CameraArmComp, 
		UStaticMeshComponent* PawnBodyComp,
		USceneComponent* VectorMeshComp
	);

	UFUNCTION(BlueprintCallable, Category = "Initialization")
	void SetBodyScreenPos(FVector2D NewBodyPos);

#pragma region Interfaces
	void OverlappedWaypoint_Implementation(ARacingWaypointActor* OverlappedWaypointActor) override;
#pragma endregion
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	// virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn Components")
	/// <summary>
	/// Root Component of this Pawn
	/// </summary>
	USceneComponent* Root;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn Components")
	/// <summary>
	/// Camera of this RacingPawn
	/// </summary>
	UCameraComponent* PawnCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn Components")
	/// <summary>
	/// Camera Spring Arm of this RacingPawn
	/// </summary>
	USpringArmComponent* CameraArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn Components")
	/// <summary>
	/// Body StaticMesh of this Pawn
	/// </summary>
	UStaticMeshComponent* PawnBody;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn Components")
	/// <summary>
	/// Body StaticMesh of this Pawn
	/// </summary>
	USceneComponent* VectorMesh;

protected:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Pawn Movement")
	void ApplyForces();
	virtual void ApplyForces_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Pawn Movement")
	void CameraArmTickMovement();
	virtual void CameraArmTickMovement_Implementation();

private:
	UPROPERTY(EditAnywhere)
	float AccelerationMagnitude = 10.0f;

	UPROPERTY(EditAnywhere)
	float MinCameraArmLength = 2.0f;

	UPROPERTY(EditAnywhere)
	float MaxCameraArmLength = 20.0f;

	UPROPERTY(EditAnywhere)

	float ZoomDeltaScale = 10.0f;

	UPROPERTY(EditAnywhere)

	float TurnDeltaScale = 10.0f;

	UPROPERTY(VisibleAnywhere)
	FVector2D BodyScreenPos = { 0, 0 };

	UPROPERTY(VisibleAnywhere)
	FVector2D AccelerateDirection = { 0, 0 };

	bool IsAccelerating = false;
	bool IsCameraTurning = false;
};
