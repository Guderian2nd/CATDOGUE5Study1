// Fill out your copyright notice in the Description page of Project Settings.


#include "WaypointsCourseActor.h"
#include "RacingWaypointActor.h"

// Sets default values
AWaypointsCourseActor::AWaypointsCourseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

bool AWaypointsCourseActor::IsOverlappedWaypointValid(ARacingWaypointActor* Waypoint, int CurrentWaypointNum)
{
	if (CurrentWaypointNum < Waypoints.Num())
	{
		if (Waypoints[CurrentWaypointNum] == Waypoint) return true;
	}
	return false;
}

int AWaypointsCourseActor::GetTotalWaypointsNum()
{
	return Waypoints.Num();
}

ARacingWaypointActor* AWaypointsCourseActor::GetWaypoint(int Index)
{
	if (Waypoints.IsValidIndex(Index)) return Waypoints[Index];
	else return nullptr;
}

// Called when the game starts or when spawned
void AWaypointsCourseActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWaypointsCourseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

