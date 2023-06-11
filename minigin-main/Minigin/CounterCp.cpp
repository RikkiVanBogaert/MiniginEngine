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

void CounterCp::SetAmount(int newAmount)
{
	m_Counter = newAmount;
}

int CounterCp::GetAmount() const
{
	return m_Counter;
}

