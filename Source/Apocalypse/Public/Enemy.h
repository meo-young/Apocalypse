#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "Apocalypse/ApocalypseCharacter.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UCLASS()
class APOCALYPSE_API AEnemy : public ACharacter
{
	GENERATED_BODY()
	
public:	
	AEnemy();

	// 데미지 받는 로직
	void GetDamage(const int Damage);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	bool bCanAttack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	bool bIsDead;
	bool bIsAttacking;


protected:
	// 최대체력
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stat")
	int MaxHealth;

	// 공격력
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stat")
	int AttackPower;

	// 이동속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stat")
	float MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stat")
	float RotationSpeed;

	// 공격 반경
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stat")
	int AttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stat")
	UWidgetComponent* OverHeadWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Target")
	AApocalypseCharacter* Target;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	TArray<TSubclassOf<ABaseItem>> DropItems;

	// 공격
	virtual void Attack() PURE_VIRTUAL(AEnemy::Attack, );
	
	int CurrentHealth;
	FTimerHandle AttackTimerHandle;
	
	void DetectTarget();
	void FollowTarget(float DeltaTime);
	void StartAttack();
	void FinishAttack();

private:
	// 사망
	void OnDeath();
	void UpdateOverheadHP();
	void SpawnItem();

	virtual void BeginPlay() override;
};

