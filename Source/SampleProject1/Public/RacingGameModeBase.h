// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RacingGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SAMPLEPROJECT1_API ARacingGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Init Properties")
	void InitCourses();
	virtual void InitCourses_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Init Properties")
	void AssignCoursesToPlayerControllers();
	virtual void AssignCoursesToPlayerControllers_Implementation();

private:
	UPROPERTY(EditAnywhere, Category = "Waypoints")
	TArray<class AWaypointsCourseActor*> Courses = {};

	UPROPERTY(EditAnywhere, Category = "Waypoints")
	FName CourseTag;


};
