
#include "FallGuysGameMode.h"
#include "FallGuysCharacter.h"
#include "UObject/ConstructorHelpers.h"


AFallGuysGameMode::AFallGuysGameMode()
{
	// set default pawn class to our Blueprinted character
	/*
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	*/
}
