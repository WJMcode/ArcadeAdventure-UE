// Copyright Epic Games, Inc. All Rights Reserved.

#include "ArcadeAdventureGameMode.h"
#include "ArcadeAdventureCharacter.h"
#include "UObject/ConstructorHelpers.h"

AArcadeAdventureGameMode::AArcadeAdventureGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
