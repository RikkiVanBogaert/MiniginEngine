#include "CounterCp.h"
#include "TextComponent.h"
#include "GameObject.h"

using namespace dae;

CounterCp::CounterCp(GameObject* owner, int startAmount):
ComponentBase(owner),
	m_Counter{ startAmount }
{}

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

