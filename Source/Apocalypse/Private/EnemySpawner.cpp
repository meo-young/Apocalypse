#include "EnemySpawner.h"

#include "MainGameStateBase.h"
#include "MeleeEnemy.h"
#include "Apocalypse/ApocalypseCharacter.h"

AEnemySpawner::AEnemySpawner() : Target(nullptr)
{
	PrimaryActorTick.bCanEverTick = false;
}


void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

	Target = Cast<AApocalypseCharacter>(GetAttachParentActor());

	GetSpawnerLocations();

	GetWorldTimerManager().SetTimer(
		SpawnTimer,
		this,
		&AEnemySpawner::SpawnEnemy,
		SpawnInterval,
		true
		);
}


// 타겟 기준으로 SpawnRadius 반경으로 원을 이루는 SpawnerCount 개의 점을 계산
FVector AEnemySpawner::GetSpawnerLocations()
{
	FVector CenterPos = Target->GetActorLocation();
	int RandNum = FMath::RandRange(1, SpawnerCount);
	float AngleStep = 360.0f / SpawnerCount;
	
	float Angle = FMath::DegreesToRadians(RandNum * AngleStep);
	float X = CenterPos.X + SpawnRadius * FMath::Cos(Angle);
	float Y = CenterPos.Y + SpawnRadius * FMath::Sin(Angle);

	return FVector(X, Y, CenterPos.Z);
}


void AEnemySpawner::SpawnEnemy()
{
	UWorld* World = GetWorld();
	if (!World)	return;

	AMainGameStateBase* GameStateBase = GetWorld()->GetGameState<AMainGameStateBase>();
	int CurrentLevel = GameStateBase->GetCurrentLevel();

	FVector SpawnLocation = GetSpawnerLocations();

	if (CurrentLevel >= 3)
	{
		SpawnLocation.X += 500.0f;
		SpawnLocation.Y += 500.0f;
		SpawnLocation.Z += 2000.0f;
		Cast<AEnemy>(World->SpawnActor<AActor>(Enemies[2], SpawnLocation, FRotator(0, 0, 0)));
		Destroy();
		return;
	}


	AEnemy* Enemy = Cast<AEnemy>(World->SpawnActor<AActor>(Enemies[CurrentLevel-1], SpawnLocation, FRotator(0, 0, 0)));
}


