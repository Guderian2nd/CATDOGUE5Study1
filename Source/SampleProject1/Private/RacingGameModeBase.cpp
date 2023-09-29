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
		auto RacingPlayerController = Cast<AMyRacingPlayerControllerBase>(PlayerControllers[i]);
		if (RacingPlayerController && Courses.Num() > 0)
		{
			RacingPlayerController->SetCourse(Courses[i % Courses.Num()]);
		}
	}
}
