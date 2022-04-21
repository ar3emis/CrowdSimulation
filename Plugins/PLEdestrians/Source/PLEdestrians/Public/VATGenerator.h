// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/SkeletalMeshComponent.h"
#include "Engine/SkeletalMesh.h"
#include "MeshUtilities.h"
#include "RawMesh.h"


#include "VATGenerator.generated.h"

UCLASS()
class PLEDESTRIANS_API AVATGenerator : public AActor
{
	GENERATED_BODY()
	
private:

	FTransform GetWorldTransformForBone(UAnimSequence* AnimSequence, const FName& InBoneName, float Seconds);
	void CalcBoneVertInfos(USkeletalMesh* SkeletalMesh, TArray<FBoneVertInfo>& Infos, bool bOnlyDominant);
	int32 GetDominantBoneIndex(FSoftSkinVertex* SoftVert);

public:	
	// Sets default values for this actor's properties
	AVATGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void CreateStaticMesh();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "VAT")
		USkeletalMesh* SkinnedMesh;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "VAT")
		TArray<UAnimSequence*> AnimationClips;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "VAT")
		int32 FrameRate;

	UFUNCTION(BlueprintCallable, Category = "VAT")
		UTexture2D* GenerateVAT();

};
