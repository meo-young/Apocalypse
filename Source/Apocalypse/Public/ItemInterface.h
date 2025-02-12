#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ItemInterface.generated.h"


UINTERFACE(MinimalAPI)
class UItemInterface : public UInterface
{
	GENERATED_BODY()
};

class APOCALYPSE_API IItemInterface
{
	GENERATED_BODY()

public:
	UFUNCTION() // 런타임에 찾기위해
	virtual void OnItemOverlap(
		UPrimitiveComponent* OverlapComp, //  오버랩이 발생한 자기자신. 스피어 컴포넌트
		AActor* OtherActor, // 스피어 컴포넌트에 부딪힌 상대
		UPrimitiveComponent* OtherComp, // 상대의 컴포넌트. CapsuleComponent
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	) = 0;
	UFUNCTION()
	
	virtual void OnItemEndOverlap(
		UPrimitiveComponent* OverlapComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex
		) = 0;
	
	virtual void ActivateItem(AActor* Activator) = 0;
};
