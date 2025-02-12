#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "MeleeEnemy.generated.h"

UCLASS()
class APOCALYPSE_API AMeleeEnemy : public AEnemy
{
	GENERATED_BODY()

public:
	AMeleeEnemy();
	
private:
	virtual void Attack() override;
	virtual void Tick(float DeltaTime) override;
	
};
