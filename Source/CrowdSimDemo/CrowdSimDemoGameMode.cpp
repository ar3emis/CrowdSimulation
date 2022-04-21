// Copyright Epic Games, Inc. All Rights Reserved.

#include "CrowdSimDemoGameMode.h"
#include "CrowdSimDemoCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACrowdSimDemoGameMode::ACrowdSimDemoGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
