// Fill out your copyright notice in the Description page of Project Settings.


#include "GoalActors/SplinePathActor.h"

// Sets default values
ASplinePathActor::ASplinePathActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootBillboard = CreateDefaultSubobject<UBillboardComponent>("RootBillboard");
	RootComponent = RootBillboard;
	
	SplineComponent = CreateDefaultSubobject<USplineComponent>("PathSpline");
	SplineComponent->SetRelativeRotation(FRotator(0, 0, 0));
	SplineComponent->AttachToComponent(RootBillboard, FAttachmentTransformRules::KeepRelativeTransform);
	SplineComponent->EditorTangentColor = FLinearColor(1,0,0,1);

}

// Called when the game starts or when spawned
void ASplinePathActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASplinePathActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

