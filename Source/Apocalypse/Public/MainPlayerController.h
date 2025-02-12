#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"


UCLASS()
class APOCALYPSE_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	void AssaultRifleFire();

	int AttackPower;
	
	
};
