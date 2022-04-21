// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PLEAgentBase.h"
#include "Components/ChildActorComponent.h"
#include "PLEHomeActor.h"

#include "Components/SkeletalMeshComponent.h"

#if WITH_EDITOR  

#include "LevelEditor.h"
#include "Editor/EditorEngine.h"
#include "Editor.h"

#endif

#include "PLEAgentGroup.generated.h"

UENUM(BlueprintType)
enum class EAgentLayout : uint8
{
	Grid   UMETA(DisplayName = "Grid"),
	Navmesh   UMETA(DisplayName = "Navmesh"),
	Custom 	    UMETA(DisplayName = "Custom"),
};

UCLASS()
class PLEDESTRIANS_API APLEAgentGroup : public AActor
{
	GENERATED_BODY()
	
private:
	static UWorld* GetGameWorld();
	void SetAgentGoal(APLEAgentBase* AgentActor, TMap<TSubclassOf<AActor>, TArray<AActor*>> GoalActorClassMap);
public:	
	// Sets default values for this actor's properties
	APLEAgentGroup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	bool MultiObjectsTrace(FVector startlocation, FVector endlocation, TArray<FHitResult> &OutHits);
	bool GroundTrace(FVector startlocation, FVector endlocation,
	FHitResult &OutHit);

	UPROPERTY()
		TArray<UChildActorComponent*> AgentCharacterComponents;

	UPROPERTY()
	TArray<UChildActorComponent*> ChildActors;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Agent")
		int32 NumberOfAgents;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Agent")
		EAgentLayout  AgentLayout;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Agent")
		TArray<TSubclassOf<APLEAgentBase>> AgentCharacterClasses;

	UFUNCTION(BlueprintCallable, Category = "Agent")
		void SpawnAgents();

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Goal")
	    TSubclassOf<AActor> DefaultGoalActorClass;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Agent")
	   TArray<APLEAgentBase*> CustomAgents;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Home")
		TArray<APLEHomeActor*> HomeActors;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Home")
	float  DefaultSpawnRadius;

};
