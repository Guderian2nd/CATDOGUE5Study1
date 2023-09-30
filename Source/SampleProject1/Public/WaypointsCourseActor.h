// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WaypointsCourseActor.generated.h"

UCLASS()
class SAMPLEPROJECT1_API AWaypointsCourseActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWaypointsCourseActor();

	UFUNCTION(BlueprintCallable, Category = "Update Waypoints")
	bool OverlappedWaypoint(class ARacingWaypointActor* Waypoint, int CurrentWaypointNum);

	UFUNCTION(BlueprintCallable, Category = "Course Info")
	int GetTotalWaypointsNum();

	UFUNCTION(BlueprintCallable, Category = "Course Info")
	ARacingWaypointActor* GetWaypoint(int Index);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(EditAnywhere, Category = "Waypoints")
	TArray<ARacingWaypointActor*> Waypoints = {};

};
