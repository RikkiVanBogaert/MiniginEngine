#include "DerCounterCps.h"
#include "GameObject.h"
#include "PlayerManager.h"


void HealthCp::ChangeAmount(int difference)
{
	CounterCp::ChangeAmount(difference);

	if (GetCounter() <= 0)
	{
		m_pOwner->MarkForDeletion();
	}
}

void HealthCp::SetAmount(int newHealth)
{
	CounterCp::SetAmount(newHealth);

	if (GetCounter() <= 0)
	{
		m_pOwner->MarkForDeletion();
	}
}

void LivesCp::ChangeAmount(int difference)
{
	CounterCp::ChangeAmount(difference);
	if (GetCounter() <= 0)
	{
		PlayerManager::GetInstance().RemovePlayerFromScene(m_pOwner);
	}
}