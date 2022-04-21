// Fill out your copyright notice in the Description page of Project Settings.


#include "PLEAgentBase.h"

#include "PLECrowdAIController.h"


// Sets default values
APLEAgentBase::APLEAgentBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void APLEAgentBase::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void APLEAgentBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APLEAgentBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

