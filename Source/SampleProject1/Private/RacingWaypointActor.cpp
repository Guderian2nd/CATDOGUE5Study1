// Fill out your copyright notice in the Description page of Project Settings.


#include "RacingWaypointActor.h"
#include "Components/BoxComponent.h"

// Sets default values
ARacingWaypointActor::ARacingWaypointActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARacingWaypointActor::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ARacingWaypointActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

