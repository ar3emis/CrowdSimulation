// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SplineComponent.h"
#include "Components/BillboardComponent.h"
#include "GameFramework/Actor.h"
#include "SplinePathActor.generated.h"

UCLASS()
class PLEDESTRIANS_API ASplinePathActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASplinePathActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Billboard")
	UBillboardComponent* RootBillboard;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Spline")
	USplineComponent* SplineComponent;

};
