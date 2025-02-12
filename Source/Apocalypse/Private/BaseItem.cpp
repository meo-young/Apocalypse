#include "BaseItem.h"

#include "Components/SphereComponent.h"

ABaseItem::ABaseItem()
{
	PrimaryActorTick.bCanEverTick = true;

	// 씬 컴포넌트 생성
	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(Scene);

	// 스피어 콜리전 컴포넌트 생성
	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->SetupAttachment(Scene);
	Collision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	
	// 스태틱 메시 컴포넌트 생성
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(Collision);

	// 이벤트 바인딩
	Collision->OnComponentBeginOverlap.AddDynamic(this, &ABaseItem::OnItemOverlap);
	Collision->OnComponentEndOverlap.AddDynamic(this, &ABaseItem::OnItemEndOverlap);
}

void ABaseItem::OnItemOverlap(
		UPrimitiveComponent* OverlapComp, //  오버랩이 발생한 자기자신. 스피어 컴포넌트
		AActor* OtherActor, // 스피어 컴포넌트에 부딪힌 상대
		UPrimitiveComponent* OtherComp, // 상대의 컴포넌트. CapsuleComponent
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Display, TEXT("OnItemOverlap, OtherActor %s"), *OtherActor->GetName());
	if (OtherActor && OtherActor->ActorHasTag("Player"))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::Printf(TEXT("Overlap!")));
		ActivateItem(OtherActor);
	}
}

void ABaseItem::OnItemEndOverlap(
		UPrimitiveComponent* OverlapComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex
		)
{
}

void ABaseItem::ActivateItem(AActor* Activator)
{
	
}

void ABaseItem::DestroyItem()
{
	Destroy();
}

