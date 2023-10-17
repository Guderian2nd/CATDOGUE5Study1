// Fill out your copyright notice in the Description page of Project Settings.


#include "RacingPawn.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "RacingControllerInterface.h"
#include "WaypointsCourseActor.h"

// Sets default values
ARacingPawn::ARacingPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ARacingPawn::AcceleratePawn_Implementation(bool TurnOnAcceleration)
{
	if (TurnOnAcceleration)
	{
		AccelerationScriptDelegate.Clear();
		AccelerationScriptDelegate.BindUFunction(this, TEXT("ApplyForces"));
		OnTick.Add(AccelerationScriptDelegate);
		//OnTick.Remove(AccelerationDelegateHandle);
		//AccelerationDelegateHandle = OnTick.AddUObject(this, &ARacingPawn::ApplyForces);
	}
	else
	{
		OnTick.Remove(AccelerationScriptDelegate);
		//OnTick.Remove(AccelerationDelegateHandle);
	}
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
	if (IsCameraTurningOn)
	{
		CameraArmMovementScriptDelegate.Clear();
		CameraArmMovementScriptDelegate.BindUFunction(this, TEXT("CameraArmTickMovement"));
		OnTick.Add(CameraArmMovementScriptDelegate);
		//OnTick.Remove(AccelerationDelegateHandle);
		//AccelerationDelegateHandle = OnTick.AddUObject(this, &ARacingPawn::ApplyForces);
	}
	else
	{
		OnTick.Remove(CameraArmMovementScriptDelegate);
		//OnTick.Remove(AccelerationDelegateHandle);
	}
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

void ARacingPawn::OverlappedWaypoint_Implementation(ARacingWaypointActor* OverlappedWaypointActor)
{
	IRacingControllerInterface::Execute_OverlappedWaypoint(Controller, OverlappedWaypointActor);
}

void ARacingPawn::ApplyForces_Implementation(float DeltaTime)
{
	if (CameraArm && PawnBody)
	{
		auto TrueAccelDirection = FRotator(0, CameraArm->GetRelativeRotation().Yaw, 0).RotateVector(FVector(AccelerateDirection.Y, AccelerateDirection.X, 0));
		PawnBody->AddForce(AccelerationMagnitude * TrueAccelDirection);
	}
}

void ARacingPawn::CameraArmTickMovement_Implementation(float DeltaTime)
{
	if (Controller->Implements<URacingControllerInterface>())
	{
		auto MouseDelta = IRacingControllerInterface::Execute_GetMousePosXYDelta(Controller);
		if (CameraArm) CameraArm->AddRelativeRotation(TurnDeltaScale * FRotator(MouseDelta.Y, MouseDelta.X, 0));
	}
}

// Called every frame
void ARacingPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	OnTick.Broadcast(DeltaTime);
}

/**
// Called to bind functionality to input
void ARacingPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
//*/
