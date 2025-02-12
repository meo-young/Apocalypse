#include "MainPlayerController.h"

#include "Enemy.h"
#include "Apocalypse/ApocalypseCharacter.h"
#include "Blueprint/UserWidget.h"


void AMainPlayerController::AssaultRifleFire()
{
	int32 ScreenWidth, ScreenHeight;
	GetViewportSize(ScreenWidth, ScreenHeight); // 화면 크기 가져오기

	FVector WorldLocation, WorldDirection;
	if (DeprojectScreenPositionToWorld(ScreenWidth * 0.5f, ScreenHeight * 0.5f, WorldLocation, WorldDirection))
	{
		// 화면 중앙에서 10,000 유닛 앞으로 라인 트레이스
		FVector End = WorldLocation + (WorldDirection * 10000.0f);

		FHitResult HitResult;
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(GetPawn()); // 플레이어 자신 제외

		bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, WorldLocation, End, ECC_Visibility, Params);

		if (bHit && HitResult.GetActor())
		{
			AEnemy* Enemy = Cast<AEnemy>(HitResult.GetActor());
			if (Enemy)
			{
				AApocalypseCharacter* ApocalypseCharacter = Cast<AApocalypseCharacter>(GetPawn());
				AttackPower = ApocalypseCharacter->GetPower();
				Enemy->GetDamage(AttackPower);
			}
		}

		// 라인 트레이스 디버깅 (에디터에서 시각적으로 확인)
		//DrawDebugLine(GetWorld(), WorldLocation, End, FColor::Blue, false, 2.0f, 0, 2.0f);
	}
}

