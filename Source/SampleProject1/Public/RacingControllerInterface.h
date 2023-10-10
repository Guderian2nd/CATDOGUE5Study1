// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "RacingControllerInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(BlueprintType)
class URacingControllerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SAMPLEPROJECT1_API IRacingControllerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Provide Pawn with Info")
	FVector2D GetMousePosXYDelta();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Course Info")
	class AWaypointsCourseActor* GetCourse();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Course Info")
	void OverlappedWaypoint(class ARacingWaypointActor* Waypoint);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Course Info")
	void SetCourse(AWaypointsCourseActor* NewCourse);
};
