#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "AtkItem.generated.h"


UCLASS()
class APOCALYPSE_API AAtkItem : public ABaseItem
{
	GENERATED_BODY()

public:
	AAtkItem();

	virtual void ActivateItem(AActor* Activator) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 AtkAmount;
	
	
};
