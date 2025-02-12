#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "Apocalypse/ApocalypseCharacter.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

UCLASS()
class APOCALYPSE_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	AEnemySpawner();

	void SpawnEnemy();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	float SpawnInterval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	int SpawnerCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	float SpawnRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	TArray<TSubclassOf<AActor>> Enemies;
	
	AApocalypseCharacter* Target;
	TArray<FVector> SpawnLocations;
	FTimerHandle SpawnTimer;


private:
	FVector GetSpawnerLocations();

};
