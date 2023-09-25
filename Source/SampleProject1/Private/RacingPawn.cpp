// Fill out your copyright notice in the Description page of Project Settings.


#include "RacingPawn.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "MyRacingPlayerControllerBase.h"

// Sets default values
ARacingPawn::ARacingPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ARacingPawn::AcceleratePawn_Implementation(bool TurnOnAcceleration)
{
	IsAccelerating = TurnOnAcceleration;
	SetArrowColor(TurnOnAcceleration);
}

void ARacingPawn::SetAccelerateVector_Implementation(FVector2D MouseScreenPos)
{
	AccelerateDirection = (MouseScreenPos - BodyScreenPos).GetSafeNormal(0.0001);
	if (VectorMesh && PawnBody)
	{
		auto TrueAccelDirection = FRotator(0, CameraArm->GetRelativeRotation().Yaw, 0).RotateVector(FVector(AccelerateDirection.Y, AccelerateDirection.X, 0));
		auto AccelDirectionWorld = Root->GetComponentTransform().TransformVector(TrueAccelDirection);
		VectorMesh->SetWorldRotation(FQuat::FindBetween(FVector::ForwardVector, AccelDirectionWorld));
	}
}

void ARacingPawn::TurnPawnCamera_Implementation(bool IsCameraTurningOn)
{
	IsCameraTurning = IsCameraTurningOn;
}

void ARacingPawn::ZoomPawnCamera_Implementation(float DeltaZoomValue)
{
	if (CameraArm)
	{
		auto TempTargetArmLength = CameraArm->TargetArmLength + ZoomDeltaScale * DeltaZoomValue;
		CameraArm->TargetArmLength = FMath::Clamp(TempTargetArmLength, MinCameraArmLength, MaxCameraArmLength);
	}
}

void ARacingPawn::ComponentsInitializeBP(
	USceneComponent* RootComp,
	UCameraComponent* PawnCameraComp,
	USpringArmComponent* CameraArmComp,
	UStaticMeshComponent* PawnBodyComp,
	USceneComponent* VectorMeshComp
)
{
	Root = RootComp;
	PawnCamera = PawnCameraComp;
	CameraArm = CameraArmComp;
	PawnBody = PawnBodyComp;
	VectorMesh = VectorMeshComp;
}

void ARacingPawn::SetBodyScreenPos(FVector2D NewBodyPos)
{
	BodyScreenPos = NewBodyPos;
}

void ARacingPawn::ApplyForces_Implementation()
{
	if (IsAccelerating)
	{
		if (CameraArm && PawnBody)
		{
			auto TrueAccelDirection = FRotator(0, CameraArm->GetRelativeRotation().Yaw, 0).RotateVector(FVector(AccelerateDirection.Y, AccelerateDirection.X, 0));
			PawnBody->AddForce(AccelerationMagnitude * TrueAccelDirection);
		}
	}
}

void ARacingPawn::CameraArmTickMovement_Implementation()
{
	if (IsCameraTurning)
	{
		if (auto RacingPlayerController = Cast<AMyRacingPlayerControllerBase>(Controller))
		{
			auto MouseDelta = RacingPlayerController->GetMousePosXYDelta();
			if (CameraArm) CameraArm->AddRelativeRotation(TurnDeltaScale * FRotator(MouseDelta.Y, MouseDelta.X, 0));
		}
	}
}

// Called every frame
void ARacingPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ApplyForces();
	CameraArmTickMovement();
}

/**
// Called to bind functionality to input
void ARacingPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
//*/