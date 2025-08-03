// Copyright Epic Games, Inc. All Rights Reserved.


#include "good_gameGameModeBase.h"

Agood_gameGameModeBase::Agood_gameGameModeBase() : Super()
{
	ConstructorHelpers::FClassFinder<APawn> MainCharacter(TEXT("/Game/MainCharacter/BP_Warrior"));

	DefaultPawnClass = MainCharacter.Class;
}
