// Fill out your copyright notice in the Description page of Project Settings.


#include "RacingWaypointActor.h"
#include "Components/BoxComponent.h"
#include "RacingPawnInterface.h"

// Sets default values
ARacingWaypointActor::ARacingWaypointActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ARacingWaypointActor::CallOverlappedWaypoint(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IRacingPawnInterface::Execute_OverlappedWaypoint(OtherActor, this);
}

// Called when the game starts or when spawned
void ARacingWaypointActor::BeginPlay()
{
	Super::BeginPlay();

	BindEvents();
}

// Called every frame
void ARacingWaypointActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARacingWaypointActor::BindEvents()
{
	OnCollisionBoxOverlap.BindUFunction(this, TEXT("CallOverlappedWaypoint"));
	WaypointCollisionBox->SetGenerateOverlapEvents(true);
	WaypointCollisionBox->OnComponentBeginOverlap.Add(OnCollisionBoxOverlap);
}

