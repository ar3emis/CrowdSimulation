// Fill out your copyright notice in the Description page of Project Settings.


#include "PLEHomeActor.h"

// Sets default values
APLEHomeActor::APLEHomeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Radius = 1000;

}

// Called when the game starts or when spawned
void APLEHomeActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APLEHomeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

