// Copyright Epic Games, Inc. All Rights Reserved.

#include "AutoTestsUnrealGameMode.h"
#include "AutoTestsUnrealCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAutoTestsUnrealGameMode::AAutoTestsUnrealGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
