#include "MainGameStateBase.h"

#include "Apocalypse/ApocalypseCharacter.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

AMainGameStateBase::AMainGameStateBase()
{
	Score = 0;
	CurrentLevel = 1;
	MaxLevel = 3;
}

void AMainGameStateBase::BeginPlay()
{
	Super::BeginPlay();
	
	if (CrosshairWidgetClass)
	{
		CrosshairWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), CrosshairWidgetClass);
		CrosshairWidgetInstance->AddToViewport();

		ScoreText = Cast<UTextBlock>(CrosshairWidgetInstance->GetWidgetFromName("ScoreText"));
		WaveText = Cast<UTextBlock>(CrosshairWidgetInstance->GetWidgetFromName("WaveText"));
		HPText = Cast<UTextBlock>(CrosshairWidgetInstance->GetWidgetFromName("HPText"));
	}

	GetWorldTimerManager().SetTimer(
		TimerHandle,
		this,
		&AMainGameStateBase::StageUp,
		LevelIntervalTime,
		true);

	GetWorldTimerManager().SetTimer(
		HUDTimerHandle,
		this,
		&AMainGameStateBase::UpdateHUD,
		0.1f,
		true);
}

void AMainGameStateBase::UpdateHUD()
{
	ScoreText->SetText(FText::FromString(FString::Printf(TEXT("Score : %d"), Score)));
	WaveText->SetText(FText::FromString(FString::Printf(TEXT("Wave : %d"), CurrentLevel)));

	AApocalypseCharacter* ApocalypseCharacter  = Cast<AApocalypseCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), AApocalypseCharacter::StaticClass()));
	HPText->SetText(FText::FromString(FString::Printf(TEXT("HP : %d"), ApocalypseCharacter->GetHP())));
}

void AMainGameStateBase::AddScore(const int Amount)
{
	Score += Amount;
	UE_LOG(LogTemp, Warning, TEXT("Score: %d"), Score);
}

void AMainGameStateBase::StageUp()
{
	UE_LOG(LogTemp, Warning, TEXT("Stage Up ! Current level: %d"), CurrentLevel);
	++CurrentLevel;

	if (CurrentLevel >= MaxLevel)
	{
		GetWorldTimerManager().ClearTimer(TimerHandle);
	}
}


