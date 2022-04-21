// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PLEAgentBase.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "PLECrowdAIController.generated.h"

/**
 * 
 */
UCLASS()
class PLEDESTRIANS_API APLECrowdAIController : public AAIController
{
	GENERATED_BODY()

public:

	APLECrowdAIController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	float CoolDownTime;
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;
	UPROPERTY()
	float DistanceCovered;
	
	UPROPERTY()
	UBehaviorTreeComponent* BehaviorTreeComponent;

	UPROPERTY()
	UBlackboardComponent* BlackboardComponent;
	
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Agent")
	UBehaviorTree* BehaviorTree;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Goal")
	FVector CurrentGoal;
	
	UPROPERTY()
	APLEAgentBase* ControlledPawn;
	
	FVector FindNextGoal();
	
};
