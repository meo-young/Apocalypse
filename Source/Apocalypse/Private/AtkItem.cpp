#include "AtkItem.h"

#include "Apocalypse/ApocalypseCharacter.h"

AAtkItem::AAtkItem()
{
	AtkAmount = 2;
}

void AAtkItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);

	if (Activator && Activator->ActorHasTag("Player"))
	{
		AApocalypseCharacter* ApocalypseCharacter = Cast<AApocalypseCharacter>(Activator);
		ApocalypseCharacter->AddAtk(AtkAmount);
		DestroyItem();
	}
}