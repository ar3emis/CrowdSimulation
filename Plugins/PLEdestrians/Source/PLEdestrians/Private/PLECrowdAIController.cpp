// Fill out your copyright notice in the Description page of Project Settings.


#include "PLECrowdAIController.h"

#include "NavigationSystem.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Navigation/CrowdFollowingComponent.h"



APLECrowdAIController::APLECrowdAIController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UPathFollowingComponent>(TEXT("PathFollowingComponent")))
{
	DistanceCovered = 0;
	CoolDownTime = 0;
}

void APLECrowdAIController::BeginPlay()
{
	Super::BeginPlay();

	if(BehaviorTree)
	{

		RunBehaviorTree(BehaviorTree);
	}

	CurrentGoal = FindNextGoal();
}

void APLECrowdAIController::OnPossess(APawn* in_pawn)
{
	Super::OnPossess(in_pawn);

	if(in_pawn)
	{
		ControlledPawn = Cast<APLEAgentBase>(in_pawn);
	}
	
	// if(BlackboardComponent)
	// {
	// 	BlackboardComponent->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	// 	
	// }
}

void APLECrowdAIController::Tick(float delta_time)
{

	Super::Tick(delta_time);

	if(CoolDownTime > 0.1)
	{
		CoolDownTime = 0;
		CurrentGoal = FindNextGoal();
		
	}

	CoolDownTime += delta_time;
}

FVector APLECrowdAIController::FindNextGoal()
{
	if(ControlledPawn)
	{
		if(ControlledPawn->CustomPath)
		{
			if(USplineComponent* CurrentSpline = ControlledPawn->CustomPath->SplineComponent)
			{
				if(DistanceCovered < CurrentSpline->GetSplineLength())
				{
					FVector CurrentLocation = CurrentSpline->GetLocationAtDistanceAlongSpline(DistanceCovered, ESplineCoordinateSpace::World);
					float DistanceToLocation = (ControlledPawn->GetActorLocation() - CurrentLocation).Size();
					if(DistanceToLocation < 150)
					{
						DistanceCovered += 200;
						return CurrentGoal;
					}
					else
					{
						
						FHitResult OutHit;

						FVector EndLocation = ControlledPawn->GetActorLocation() + ControlledPawn->GetControlRotation().Vector() * 50;
						FCollisionQueryParams RV_TraceParams = FCollisionQueryParams(FName(TEXT("RV_Trace")), true, this);
						RV_TraceParams.bTraceComplex = true;
						RV_TraceParams.bReturnPhysicalMaterial = false;
						RV_TraceParams.AddIgnoredActor(ControlledPawn);
						
						bool linetraceresult = GetWorld()->LineTraceSingleByChannel(
							OutHit,        //result
							ControlledPawn->GetActorLocation(),    //start
							EndLocation, //end
							ECC_Pawn, //collision channel
							RV_TraceParams
						);

						FVector RandomDeviation = FVector(0,0,0);
						FVector AverageLocation ;
						bool bValidTrace = false;
						if(linetraceresult)
						{
							if(AActor* HitActor = OutHit.GetActor())
							{
								if(APLEAgentBase* AgentActor = Cast<APLEAgentBase>(HitActor))
								{
									RandomDeviation = FVector(10, 10, 0);
									AverageLocation = AgentActor->GetActorLocation() - ControlledPawn->GetControlRotation().Vector() * 100;
									bValidTrace = true;
									
								}
							}
							
						}

						ControlledPawn->GetCharacterMovement()->MaxWalkSpeed = bValidTrace ? 0 : 150;

						
						FVector NewGoal = CurrentLocation;
						if(DistanceCovered > 0)
						{
							float RandomDeviationX = FMath::RandRange(-40, 40);
							float RandomDeviationY = FMath::RandRange(-40, 40);
							NewGoal += FVector(RandomDeviationX, RandomDeviationY, 0);
						}
						
						UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
						if (NavSys)
						{
							ANavigationData* UseNavData = NavSys->GetDefaultNavDataInstance(FNavigationSystem::Create);
							if (UseNavData)
							{
								FNavLocation RandomPoint;
								if (NavSys->GetRandomPointInNavigableRadius(NewGoal, 100, RandomPoint, UseNavData, UNavigationQueryFilter::GetQueryFilter(*UseNavData, this, nullptr)))
								{
									NewGoal = RandomPoint.Location;
								}
							}
						}
						
						NewGoal += RandomDeviation;
						return NewGoal;
					}
				}
				
			}
		}
		
	}
	
	return  CurrentGoal;
}

