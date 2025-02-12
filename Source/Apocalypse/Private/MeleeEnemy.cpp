#include "MeleeEnemy.h"

#include "Apocalypse/ApocalypseCharacter.h"

AMeleeEnemy::AMeleeEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMeleeEnemy::Attack()
{
	if (bIsAttacking) return;
	
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Target->GetName());
	Target->GetDamage(AttackPower);
}

void AMeleeEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	DetectTarget();

	if (bCanAttack)
	{
		Attack();
		StartAttack();
	}
	else
	{
		FollowTarget(DeltaTime);
	}
}


