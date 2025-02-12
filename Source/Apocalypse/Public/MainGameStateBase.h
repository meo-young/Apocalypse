#pragma once

#include "CoreMinimal.h"
#include "Components/TextBlock.h"
#include "GameFramework/GameStateBase.h"
#include "MainGameStateBase.generated.h"


UCLASS()
class APOCALYPSE_API AMainGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	AMainGameStateBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level")
	float LevelIntervalTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level")
	int MaxLevel;

	int CurrentLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score")
	int Score;

	int GetScore() const { return Score; };
	int GetCurrentLevel() const { return CurrentLevel; };

	void AddScore(const int Amount);
	void StageUp();

	FTimerHandle TimerHandle;

	UTextBlock* ScoreText;
	UTextBlock* WaveText;
	UTextBlock* HPText;

	// Crosshair 위젯
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Fire")
	TSubclassOf<UUserWidget> CrosshairWidgetClass;

	// Crosshair 위젯 인스턴스
	UUserWidget* CrosshairWidgetInstance;

private:
	virtual void BeginPlay() override;
	FTimerHandle HUDTimerHandle;
	void UpdateHUD();
	
};
