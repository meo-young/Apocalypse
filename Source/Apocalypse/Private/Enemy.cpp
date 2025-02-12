#include "Enemy.h"

#include "BaseItem.h"
#include "MainGameStateBase.h"
#include "Apocalypse/ApocalypseCharacter.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"

AEnemy::AEnemy()
{
	OverHeadWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("OverHeadWidget"));
	OverHeadWidget->SetupAttachment(GetMesh());
	OverHeadWidget->SetWidgetSpace(EWidgetSpace::Screen);
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	Target = Cast<AApocalypseCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), AApocalypseCharacter::StaticClass()));
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Target->GetName());
	CurrentHealth = MaxHealth;
}

void AEnemy::DetectTarget()
{
	if (!Target) return;

	// 공격 범위내에 "플레이어"가 존재하는 경우 플래그 활성화
	float Distance = FVector::Dist(GetActorLocation(), Target->GetActorLocation());
	bCanAttack = Distance <= AttackRange;
}

void AEnemy::FollowTarget(const float DeltaTime)
{
	if (!Target) return;

	// 플레이어와 적 사이의 방향벡터 계산
	FVector ActorLocation = GetActorLocation();
	FVector TargetLocation = Target->GetActorLocation();

	// 상, 하 이동 제한
	FVector MoveDirection = TargetLocation - ActorLocation;
	MoveDirection.Z = 0;
	MoveDirection.Normalize();

	// 이동 적용
	AddMovementInput(MoveDirection, MoveSpeed * DeltaTime);

	// 타겟 방향으로 회전
	FRotator TargetRotation = FRotationMatrix::MakeFromX(MoveDirection).Rotator();
	FRotator NewRotation = FMath::RInterpTo(GetActorRotation(), TargetRotation, DeltaTime, RotationSpeed);
	SetActorRotation(NewRotation);
}

void AEnemy::StartAttack()
{
	bIsAttacking = true;

	GetWorldTimerManager().SetTimer(
		AttackTimerHandle,
		this,
		&AEnemy::FinishAttack,
		0.8f,
		false);
}

void AEnemy::FinishAttack()
{
	bIsAttacking = false;
}

void AEnemy::OnDeath()
{
	// 사망했을 때의 로직 처리
	UE_LOG(LogTemp, Warning, TEXT("%s Destroyed !"), *this->GetName());
	AMainGameStateBase* GameStateBase = GetWorld()->GetGameState<AMainGameStateBase>();
	GameStateBase->AddScore(MaxHealth);
	Destroy();
}

void AEnemy::UpdateOverheadHP()
{
	UUserWidget* OverHeadWidgetInstance = OverHeadWidget->GetUserWidgetObject();
	UTextBlock* HPText = Cast<UTextBlock>(OverHeadWidgetInstance->GetWidgetFromName("OverHeadHp"));
	HPText->SetText(FText::FromString(FString::Printf(TEXT("%d / %d"), CurrentHealth, MaxHealth)));
}

void AEnemy::SpawnItem()
{
	int RandomNum = FMath::RandRange(0, DropItems.Num() - 1);
	GetWorld()->SpawnActor<ABaseItem>(DropItems[RandomNum], GetActorLocation(), GetActorRotation());
}


void AEnemy::GetDamage(const int Damage)
{
	CurrentHealth -= Damage;
	UE_LOG(LogTemp, Warning, TEXT("%d Damaged ! Current HP : %d"), Damage, CurrentHealth);

	UpdateOverheadHP();
	
	if (CurrentHealth <= 0)
	{
		CurrentHealth = 0;
		UpdateOverheadHP();
		SpawnItem();
		OnDeath();
	}
}




