#include "CounterCp.h"
#include "TextComponent.h"
#include "GameObject.h"

using namespace dae;

CounterCp::CounterCp(GameObject* owner, int startAmount):
	m_Counter{ startAmount }
{
	m_pOwner = owner;
}

void CounterCp::ChangeAmount(int difference)
{
	m_Counter += difference;
}

void CounterCp::SetAmount(int newHealth)
{
	if (newHealth < 0)
		return;

	m_Counter = newHealth;
}

int CounterCp::GetAmount() const
{
	return m_Counter;
}

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