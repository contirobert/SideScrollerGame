// Copyright Epic Games, Inc. All Rights Reserved.

#include "SideScrollerGameGameMode.h"
#include "SideScrollerGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASideScrollerGameGameMode::ASideScrollerGameGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
