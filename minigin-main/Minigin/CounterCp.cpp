#include "CounterCp.h"
#include "GameObject.h"
#include "TextComponent.h"



using namespace dae;

CounterCp::CounterCp(GameObject* owner, int startAmount):
	m_Counter{ startAmount }
{
	m_pOwner = owner;
}

void CounterCp::ChangeAmount(int difference)
{
	m_Counter += difference;

	if (m_Counter <= 0)
	{
		m_pOwner->MarkForDeletion();
	}
}

void CounterCp::SetAmount(int newHealth)
{
	if (newHealth < 0)
		return;

	m_Counter = newHealth;

	if (m_Counter <= 0)
		m_pOwner->MarkForDeletion();
}

int CounterCp::GetAmount() const
{
	return m_Counter;
}

