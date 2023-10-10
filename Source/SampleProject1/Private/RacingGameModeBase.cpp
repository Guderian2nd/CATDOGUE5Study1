// Copyright Epic Games, Inc. All Rights Reserved.


#include "RacingGameModeBase.h"
#include "WaypointsCourseActor.h"
#include "Kismet/GameplayStatics.h"
#include "MyRacingPlayerControllerBase.h"

void ARacingGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	InitCourses();
	AssignCoursesToPlayerControllers();
}

void ARacingGameModeBase::InitCourses_Implementation()
{
	TArray<AActor*> WaypointCourses = {};
	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), AWaypointsCourseActor::StaticClass(), CourseTag, WaypointCourses);

	for (auto Course : WaypointCourses)
	{
		Courses.Add(Cast<AWaypointsCourseActor>(Course));
	}
}

void ARacingGameModeBase::AssignCoursesToPlayerControllers_Implementation()
{
	TArray<AActor*> PlayerControllers = {};
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMyRacingPlayerControllerBase::StaticClass(), PlayerControllers);

	for (auto i = 0; i < PlayerControllers.Num(); ++i)
	{
		if (PlayerControllers[i]->Implements<URacingControllerInterface>() && Courses.Num() > 0)
		{
			IRacingControllerInterface::Execute_SetCourse(PlayerControllers[i], Courses[i % Courses.Num()]);
		}
	}
}
