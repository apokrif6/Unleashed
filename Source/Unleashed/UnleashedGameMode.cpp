// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnleashedGameMode.h"
#include "UnleashedCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUnleashedGameMode::AUnleashedGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Main/Blueprints/BP_MainCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
