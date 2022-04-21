// Fill out your copyright notice in the Description page of Project Settings.


#include "VATGenerator.h"

#include "Animation/AnimSequence.h"
#include "Engine/StaticMesh.h"
#include "Rendering/SkeletalMeshModel.h"
#include "Rendering/SkeletalMeshLODModel.h"

// Sets default values
AVATGenerator::AVATGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	FrameRate = 30;
}

// Called when the game starts or when spawned
void AVATGenerator::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVATGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int32 AVATGenerator::GetDominantBoneIndex(FSoftSkinVertex* SoftVert)
{
	uint8 MaxWeightBone = 0;
	uint8 MaxWeightWeight = 0;

	for (int32 i = 0; i < MAX_TOTAL_INFLUENCES; i++)
	{
		if (SoftVert->InfluenceWeights[i] > MaxWeightWeight)
		{
			MaxWeightWeight = SoftVert->InfluenceWeights[i];
			MaxWeightBone = SoftVert->InfluenceBones[i];
		}
	}

	return MaxWeightBone;
}

void AVATGenerator::CalcBoneVertInfos(USkeletalMesh* SkeletalMesh, TArray<FBoneVertInfo>& Infos, bool bOnlyDominant)
{
	// FSkeletalMeshModel* ImportedResource = SkeletalMesh->GetImportedModel();
	// if (ImportedResource->LODModels.Num() == 0)
	// 	return;
	//
	// SkeletalMesh->CalculateInvRefMatrices();
	// check(SkeletalMesh->GetRefSkeleton().GetRawBoneNum() == SkeletalMesh->GetRefBasesInvMatrix().Num());
	//
	// Infos.Empty();
	// Infos.AddZeroed(SkeletalMesh->GetRefSkeleton().GetRawBoneNum());
	//
	// FSkeletalMeshLODModel* LODModel = &ImportedResource->LODModels[0];
	// for (int32 SectionIndex = 0; SectionIndex < LODModel->Sections.Num(); SectionIndex++)
	// {
	// 	FSkelMeshSection& Section = LODModel->Sections[SectionIndex];
	// 	for (int32 i = 0; i < Section.SoftVertices.Num(); i++)
	// 	{
	// 		FSoftSkinVertex* SoftVert = &Section.SoftVertices[i];
	//
	// 		// if (bOnlyDominant)
	// 		// {
	// 		// 	int32 BoneIndex = Section.BoneMap[GetDominantBoneIndex(SoftVert)];
	// 		//
	// 		// 	FVector LocalPos = SkeletalMesh->GetRefBasesInvMatrix()[BoneIndex].TransformPosition(SoftVert->Position);
	// 		// 	Infos[BoneIndex].Positions.Add(LocalPos);
	// 		//
	// 		// 	FVector LocalNormal = SkeletalMesh->GetRefBasesInvMatrix()[BoneIndex].TransformVector(SoftVert->TangentZ);
	// 		// 	Infos[BoneIndex].Normals.Add(LocalNormal);
	// 		// }
	// 		// else
	// 		// {
	// 		// 	for (int32 j = 0; j < MAX_TOTAL_INFLUENCES; j++)
	// 		// 	{
	// 		// 		if (SoftVert->InfluenceWeights[j] > 0)
	// 		// 		{
	// 		// 			int32 BoneIndex = Section.BoneMap[SoftVert->InfluenceBones[j]];
	// 		//
	// 		// 			FVector LocalPos = SkeletalMesh->GetRefBasesInvMatrix()[BoneIndex].TransformPosition(SoftVert->Position);
	// 		// 			Infos[BoneIndex].Positions.Add(LocalPos);
	// 		//
	// 		// 			FVector LocalNormal = SkeletalMesh->GetRefBasesInvMatrix()[BoneIndex].TransformVector(SoftVert->TangentZ);
	// 		// 			Infos[BoneIndex].Normals.Add(LocalNormal);
	// 		// 		}
	// 		// 	}
	// 		// }
	// 	}
	// }
}

FTransform AVATGenerator::GetWorldTransformForBone(UAnimSequence* AnimSequence, const FName& InBoneName, float Seconds)
{
	FName BoneName = InBoneName;
	FTransform  WorldTransform = FTransform::Identity;

	// do
	// {
	// 	int32 BoneIndex = SkinnedMesh->GetRefSkeleton().FindBoneIndex(BoneName);
	// 	FTransform BoneTransform;
	// 	int32 TrackIndex;
	//
	// 	for (TrackIndex = 0; TrackIndex < AnimSequence->GetRawTrackToSkeletonMapTable().Num(); ++TrackIndex)
	// 	{
	// 		if (AnimSequence->GetRawTrackToSkeletonMapTable()[TrackIndex].BoneTreeIndex == BoneIndex)
	// 		{
	// 			break;
	// 		}
	// 	}
	//
	// 	if (TrackIndex == AnimSequence->GetRawTrackToSkeletonMapTable().Num())
	// 	{
	// 		break;
	// 	}
	//
	// 	AnimSequence->GetBoneTransform(BoneTransform, TrackIndex, Seconds, true);
	// 	WorldTransform *= BoneTransform;
	// 	
	// 	int32 ParentIndex = SkinnedMesh->GetRefSkeleton().GetParentIndex(BoneIndex);
	// 	bool bHasValidParent = SkinnedMesh->GetRefSkeleton().IsValidIndex(ParentIndex);
	//
	// 	BoneName = bHasValidParent ? SkinnedMesh->GetRefSkeleton().GetBoneName(SkinnedMesh->GetRefSkeleton().GetParentIndex(BoneIndex)) : NAME_None;
	//
	// } while (BoneName != NAME_None);

	//WorldTransform.SetToRelativeTransform(MeshComponent->GetComponentTransform());

	return WorldTransform;
}


void  AVATGenerator::CreateStaticMesh() {

	// Object Details
	FString ObjectName = FString("MyObject");

	TArray<FVector> Vertices;
	Vertices.Add(FVector(86.6, 75, 0));
	Vertices.Add(FVector(-86.6, 75, 0));
	Vertices.Add(FVector(2.13, 25, 175));
	Vertices.Add(FVector(2.13, -75, 0));
	int numberOfVertices = Vertices.Num();

	struct Face {
		unsigned int v1;
		unsigned int v2;
		unsigned int v3;
		short materialID;
		FVector2D uvCoords1;
		FVector2D uvCoords2;
		FVector2D uvCoords3;
	};

	TArray<Face> Faces;
	Face oneFace = {1, 3, 0, 0, FVector2D(0, 0), FVector2D(1, 0), FVector2D(0.5, 1)};
	Faces.Add(oneFace);
	oneFace = { 0,2,1,  1,  FVector2D(0,0), FVector2D(1, 0), FVector2D(0.5, 1) };
	Faces.Add(oneFace);
	oneFace = { 3,2,0,  0,  FVector2D(0,0), FVector2D(1, 0), FVector2D(0.5, 1) };
	Faces.Add(oneFace);
	oneFace = { 1,2,3,  1,  FVector2D(0,0), FVector2D(1, 0), FVector2D(0.5, 1) };
	Faces.Add(oneFace);
	int numberOfFaces = Faces.Num();

	TArray<FStaticMaterial> Materials; //This should contain the real Materials, this is just an example
	Materials.Add(FStaticMaterial());
	Materials.Add(FStaticMaterial());
	int numberOfMaterials = Materials.Num();

	// Create Package
	FString pathPackage = FString("/Game/MyStaticMeshes/");
	FString absolutePathPackage = FPaths::ProjectContentDir() + "/MyStaticMeshes/";

	FPackageName::RegisterMountPoint(*pathPackage, *absolutePathPackage);

	UPackage* Package = CreatePackage(*pathPackage);

	// Create Static Mesh
	//FName StaticMeshName = MakeUniqueObjectName(Package, UStaticMesh::StaticClass(), FName(*ObjectName));
	//UStaticMesh* myStaticMesh = NewObject(Package, StaticMeshName, RF_Public | RF_Standalone);

	//if (myStaticMesh != NULL)
	//{
	//	FRawMesh myRawMesh = FRawMesh();
	//	FColor WhiteVertex = FColor(255, 255, 255, 255);
	//	FVector EmptyVector = FVector(0, 0, 0);

	//	// Vertices
	//	for (int vertIndex = 0; vertIndex < numberOfVertices; vertIndex++) {
	//		myRawMesh.VertexPositions.Add(Vertices[vertIndex]);
	//	}
	//	// Faces and UV/Normals
	//	for (int faceIndex = 0; faceIndex < numberOfFaces; faceIndex++) {
	//		myRawMesh.WedgeIndices.Add(Faces[faceIndex].v1);
	//		myRawMesh.WedgeIndices.Add(Faces[faceIndex].v2);
	//		myRawMesh.WedgeIndices.Add(Faces[faceIndex].v3);

	//		myRawMesh.WedgeColors.Add(WhiteVertex);
	//		myRawMesh.WedgeColors.Add(WhiteVertex);
	//		myRawMesh.WedgeColors.Add(WhiteVertex);

	//		myRawMesh.WedgeTangentX.Add(EmptyVector);
	//		myRawMesh.WedgeTangentX.Add(EmptyVector);
	//		myRawMesh.WedgeTangentX.Add(EmptyVector);

	//		myRawMesh.WedgeTangentY.Add(EmptyVector);
	//		myRawMesh.WedgeTangentY.Add(EmptyVector);
	//		myRawMesh.WedgeTangentY.Add(EmptyVector);

	//		myRawMesh.WedgeTangentZ.Add(EmptyVector);
	//		myRawMesh.WedgeTangentZ.Add(EmptyVector);
	//		myRawMesh.WedgeTangentZ.Add(EmptyVector);

	//		// Materials
	//		myRawMesh.FaceMaterialIndices.Add(Faces[faceIndex].materialID);

	//		myRawMesh.FaceSmoothingMasks.Add(0xFFFFFFFF); // Phong

	//		for (int UVIndex = 0; UVIndex < MAX_MESH_TEXTURE_COORDS; UVIndex++)
	//		{
	//			myRawMesh.WedgeTexCoords[UVIndex].Add(Faces[faceIndex].uvCoords1);
	//			myRawMesh.WedgeTexCoords[UVIndex].Add(Faces[faceIndex].uvCoords2);
	//			myRawMesh.WedgeTexCoords[UVIndex].Add(Faces[faceIndex].uvCoords3);
	//		}
	//	}

	//	// Saving mesh in the StaticMesh
	//	new(myStaticMesh->GetSourc) FStaticMeshSourceModel();
	//	myStaticMesh->SourceModels[0].RawMeshBulkData->SaveRawMesh(myRawMesh);

	//	FStaticMeshSourceModel& SrcModel = myStaticMesh->SourceModels[0];

	//	// Model Configuration
	//	myStaticMesh->SourceModels[0].BuildSettings.bRecomputeNormals = true;
	//	myStaticMesh->SourceModels[0].BuildSettings.bRecomputeTangents = true;
	//	myStaticMesh->SourceModels[0].BuildSettings.bUseMikkTSpace = false;
	//	myStaticMesh->SourceModels[0].BuildSettings.bGenerateLightmapUVs = true;
	//	myStaticMesh->SourceModels[0].BuildSettings.bBuildAdjacencyBuffer = false;
	//	myStaticMesh->SourceModels[0].BuildSettings.bBuildReversedIndexBuffer = false;
	//	myStaticMesh->SourceModels[0].BuildSettings.bUseFullPrecisionUVs = false;
	//	myStaticMesh->SourceModels[0].BuildSettings.bUseHighPrecisionTangentBasis = false;

	//	// Assign the Materials to the Slots (optional

	//	for (int32 MaterialID = 0; MaterialID < numberOfMaterials; MaterialID++) {
	//		myStaticMesh->StaticMaterials.Add(Materials[MaterialID]);
	//		myStaticMesh->SectionInfoMap.Set(0, MaterialID, FMeshSectionInfo(MaterialID));
	//	}

	//	// Processing the StaticMesh and Marking it as not saved
	//	myStaticMesh->ImportVersion = EImportStaticMeshVersion::LastVersion;
	//	myStaticMesh->CreateBodySetup();
	//	myStaticMesh->SetLightingGuid();
	//	myStaticMesh->PostEditChange();
	//	Package->MarkPackageDirty();

	//};
}

UTexture2D* AVATGenerator::GenerateVAT()
{
	UTexture2D* VATTexture = NULL;

	// if (SkinnedMesh && SkinnedMesh->GetSkeleton() && FrameRate > 0)
	// {
	// 	TArray<FSoftSkinVertex> SSVertices;
	// 	FSkeletalMeshModel* ImportedModel = SkinnedMesh->GetImportedModel();
	// 	if (ImportedModel)
	// 	{
	// 		int32 ImportedLODNum = ImportedModel->LODModels.Num();
	// 		int32 CurrentLODIndex = 0;
	// 		FSkeletalMeshLODModel& SkeletalMeshLodModel = ImportedModel->LODModels[CurrentLODIndex];
	//
	// 		SkeletalMeshLodModel.GetVertices(SSVertices);
	// 	}
	//
	// 	int32 NumBones = SkinnedMesh->GetRefSkeleton().GetNum();
	//
	// 	TArray<FBoneVertInfo> Infos;
	// 	CalcBoneVertInfos(SkinnedMesh, Infos, false);
	//
	//
	// 	//uint8* pixels = (uint8*)malloc(ImageSize.Y * ImageSize.X * 4);
	//
	// 	for (auto& aClip: AnimationClips)
	// 	{
	// 		if (aClip)
	// 		{
	// 			if (aClip->GetSkeleton() == SkinnedMesh->GetSkeleton())
	// 			{
	// 				
	// 				int32 Frames = aClip->GetNumberOfFrames();
	// 				float TotalTime = aClip->GetMaxCurrentTime();
	// 				float DeltaTime = 1 / FrameRate;
	//
	// 				for (float CurrentTime = 0; CurrentTime <= TotalTime; CurrentTime += DeltaTime)
	// 				{
	// 					for (int iIndex = 0; iIndex < Infos.Num(); iIndex++)
	// 					{
	// 						FName BoneName = SkinnedMesh->GetRefSkeleton().GetBoneName(iIndex);
	// 						FTransform BoneTransform = GetWorldTransformForBone(aClip, BoneName, CurrentTime);
	//
	// 						int32 CurrentFrame = Frames * CurrentTime / TotalTime;
	// 						
	// 					}
	// 				}
	//
	// 			}
	// 		}
	// 	}
	// 	//SkinnedMesh->animdat
	// }
	return VATTexture;
}