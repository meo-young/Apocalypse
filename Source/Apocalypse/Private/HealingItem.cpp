#include "HealingItem.h"

#include "Apocalypse/ApocalypseCharacter.h"

AHealingItem::AHealingItem()
{
	HealAmount = 5;
}

void AHealingItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);

	UE_LOG(LogTemp, Warning, TEXT("Activator : %s"),*Activator->GetName());

	if (Activator && Activator->ActorHasTag("Player"))
	{
		AApocalypseCharacter* ApocalypseCharacter = Cast<AApocalypseCharacter>(Activator);
		ApocalypseCharacter->AddHP(HealAmount);
		DestroyItem();
	}
}