// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GoalActors/SplinePathActor.h"
#include "PLEAgentBase.generated.h"

UCLASS()
class PLEDESTRIANS_API APLEAgentBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APLEAgentBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Goal")
		TSubclassOf<AActor> DefaultGoalActorClass;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Goal")
	    ASplinePathActor* CustomPath;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Goal")
	   AActor* GoalActor;
};
