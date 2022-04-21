// Fill out your copyright notice in the Description page of Project Settings.


#include "PLEAgentGroup.h"

#include "Landscape.h"
#include "NavigationSystem.h"
#include "Engine/StaticMeshActor.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
APLEAgentGroup::APLEAgentGroup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	NumberOfAgents = 100;
	DefaultSpawnRadius = 10000;
}

// Called when the game starts or when spawned
void APLEAgentGroup::BeginPlay()
{
	Super::BeginPlay();

	TMap<TSubclassOf<AActor>, TArray<AActor*>> GoalActorClassMap;
	
	for (int iIndex = 0; iIndex < AgentCharacterComponents.Num(); iIndex++)
	{
		if(APLEAgentBase* AgentActor = Cast<APLEAgentBase>(AgentCharacterComponents[iIndex]->GetChildActor()))
		{
			SetAgentGoal(AgentActor, GoalActorClassMap);
		}
		
	}

	for (int iIndex = 0; iIndex < CustomAgents.Num(); iIndex++)
	{
		
		SetAgentGoal(CustomAgents[iIndex], GoalActorClassMap);
	}
	
}

// Called every frame
void APLEAgentGroup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UWorld* APLEAgentGroup::GetGameWorld()
{
#if WITH_EDITOR  

	auto Client = GEditor->GetActiveViewport()->GetClient();
	if (Client)
	{
		UWorld* world = Client->GetWorld();
		return world;
	}
#endif


	if (GEngine)
	{
		UGameViewportClient* Viewport = GEngine->GameViewport;

		if (Viewport)
		{
			UWorld* world = NULL;
			FWorldContext* worldcontext = GEngine->GetWorldContextFromGameViewport(Viewport);
			world = worldcontext->World();

			return world;

		}
	}

	return NULL;

}

void APLEAgentGroup::SetAgentGoal(APLEAgentBase* AgentActor, TMap<TSubclassOf<AActor>, TArray<AActor*>> GoalActorClassMap)
{
	if(AgentActor)
	{
		if(AgentActor->CustomPath)
		{
			
		}
		else
		{
			if(!AgentActor->DefaultGoalActorClass)
			{
				AgentActor->DefaultGoalActorClass = DefaultGoalActorClass;
				
			}
			
			if(AgentActor->DefaultGoalActorClass)
			{
				if(!GoalActorClassMap.Contains(AgentActor->DefaultGoalActorClass))
				{
					TArray<AActor*> GoalActors;
					UGameplayStatics::GetAllActorsOfClass(this, AgentActor->DefaultGoalActorClass, GoalActors);
	
					GoalActorClassMap.Add(AgentActor->DefaultGoalActorClass, GoalActors);
				}

				TArray<AActor*> GoalActors = GoalActorClassMap[AgentActor->DefaultGoalActorClass];
				AActor* CurrentGoalActor = nullptr;
				float DistanceToTarget = 0;
				for (int jIndex = 0; jIndex < GoalActors.Num(); jIndex++)
				{
					if(GoalActors[jIndex])
					{
						FVector TargetLocation = GoalActors[jIndex]->GetActorLocation();
						float CurrentDistance =  (TargetLocation - AgentActor->GetActorLocation()).Size();
						if(jIndex == 0)
						{
							DistanceToTarget = CurrentDistance;
							CurrentGoalActor = GoalActors[jIndex];
						}
						else
						{
							if(DistanceToTarget > CurrentDistance)
							{
								DistanceToTarget = CurrentDistance;
								CurrentGoalActor = GoalActors[jIndex];
							}
						}
						
					}
					
				}

				AgentActor->GoalActor = CurrentGoalActor;
			}
		}
		
	}
}


bool APLEAgentGroup::MultiObjectsTrace(FVector startlocation, FVector endlocation, TArray<FHitResult> &OutHits)
{
	UWorld* world = GetGameWorld();
	if (world)
	{
		static const FName NAME_ReapplyInstancesForBrush = TEXT("ReapplyCollisionWithWorld");
		FCollisionQueryParams QueryParams(NAME_ReapplyInstancesForBrush, SCENE_QUERY_STAT_ONLY(IFA_FoliageTrace), true);
		QueryParams.bReturnFaceIndex = false;
		QueryParams.bTraceComplex = true;
		QueryParams.bReturnPhysicalMaterial = false;

		FCollisionShape SphereShape;
		SphereShape.SetSphere(10);

		bool linetraceresult = world->SweepMultiByObjectType(OutHits, startlocation, endlocation, FQuat::Identity, FCollisionObjectQueryParams(ECC_WorldStatic), SphereShape, QueryParams);
		return linetraceresult;


	}
	return false;
}



bool APLEAgentGroup::GroundTrace(FVector startlocation, FVector endlocation,
	FHitResult &OutHit)
{
	TArray<FHitResult> Hits;
	bool linetraceresult = MultiObjectsTrace(startlocation, endlocation, Hits);

	for (const FHitResult& Hit : Hits)
	{
		const AActor* HitActor = Hit.GetActor();
		if (HitActor)
		{
			if (HitActor->IsA(AStaticMeshActor::StaticClass()) || HitActor->IsA(ALandscape::StaticClass()))
			{
				OutHit = Hit;
				return true;
			}
		}
		else
		{

		}
		
	}

	return false;
}


void APLEAgentGroup::SpawnAgents()
{
	
	TArray<UActorComponent*> ChildComponents;
	GetComponents(UChildActorComponent::StaticClass(), ChildComponents);

	for (int iIndex = 0; iIndex < AgentCharacterComponents.Num(); iIndex++)
	{
		if (AgentCharacterComponents[iIndex])
		{
			AgentCharacterComponents[iIndex]->DestroyChildActor();
			AgentCharacterComponents[iIndex]->DestroyComponent();
			AgentCharacterComponents[iIndex] = nullptr;
		}
	}

	AgentCharacterComponents.Empty();

	TArray<TSubclassOf<APLEAgentBase>> ValidAgentClasses;
		for (int iIndex = 0; iIndex < AgentCharacterClasses.Num(); iIndex++)
		{
			if (AgentCharacterClasses[iIndex])
			{
				ValidAgentClasses.Add(AgentCharacterClasses[iIndex]);
			}
		}

		if(ValidAgentClasses.Num() > 0)
		{
			for (int iIndex = 0; iIndex < NumberOfAgents; iIndex++)
			{

				FVector HomeLocation;
				float Radius;
				if(HomeActors.Num() > 0)
				{
					int32 RandomHActorIndex = FMath::RandRange(0, HomeActors.Num() - 1);
					Radius = HomeActors[RandomHActorIndex]->Radius;
					HomeLocation = HomeActors[RandomHActorIndex]->GetActorLocation();
					
				}
				else
				{
					Radius = DefaultSpawnRadius;
					HomeLocation = GetActorLocation();
				}
				
				UWorld* World = GetGameWorld();
				FActorSpawnParameters SpawnInfo;
				int32 RandomIndex = ValidAgentClasses.Num() -1;

				switch (AgentLayout)
				{
				case EAgentLayout::Navmesh:
				{
					UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(World);
					if (NavSys)
					{
						ANavigationData* UseNavData = NavSys->GetDefaultNavDataInstance(FNavigationSystem::DontCreate);
						if (UseNavData)
						{
							FNavLocation RandomPoint;
							if (NavSys->GetRandomPointInNavigableRadius(HomeLocation, Radius, RandomPoint, UseNavData, UNavigationQueryFilter::GetQueryFilter(*UseNavData, this, AStaticMeshActor::StaticClass())))
							{
								FVector endlocationdown = RandomPoint.Location - FVector(0,0,50000);
								FVector endlocationup = RandomPoint.Location + FVector(0,0,50000);
								
								FHitResult OutHit;
								if (GroundTrace(RandomPoint.Location, endlocationdown, OutHit) ||
									GroundTrace(RandomPoint.Location, endlocationup, OutHit))
								{
									bool bIsValidLocation = true;
									for (int jIndex = 0; jIndex < AgentCharacterComponents.Num(); jIndex++)
									{
										FVector ActorLocation = AgentCharacterComponents[jIndex]->GetComponentLocation();
										float Distance = (ActorLocation - OutHit.Location - FVector(0,0,85)).Size();
										if(Distance < 100)
										{
											bIsValidLocation = false;
											break;
										}
									}

									if(bIsValidLocation)
									{
										FString AgentName = TEXT("AgentInstance_") + FString::FromInt(AgentCharacterComponents.Num());
										UChildActorComponent* NewPLEComponent = NewObject<UChildActorComponent>(this, UChildActorComponent::StaticClass(), *AgentName, RF_Transactional);
										NewPLEComponent->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepWorldTransform);
										NewPLEComponent->SetChildActorClass(ValidAgentClasses[RandomIndex]);
										NewPLEComponent->RegisterComponent();
										NewPLEComponent->GetChildActor()->SetActorLabel(*AgentName);
										NewPLEComponent->SetWorldLocation(OutHit.Location + FVector(0,0,85));
										AgentCharacterComponents.Add(NewPLEComponent);
									}
								}
								
							}
						}
					}

				}
				break;
				case EAgentLayout::Grid:
				{

				}
				break;
				case EAgentLayout::Custom:
				{

				}
				break;
			}
		 }
		}
	
}