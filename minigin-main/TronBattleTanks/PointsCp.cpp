#include "PointsCp.h"

PointsCp::PointsCp(dae::GameObject* owner, int startAmount) :
	ComponentBase(owner),
	m_pCounterCp(std::make_unique<dae::CounterCp>(owner, startAmount))
{}

void PointsCp::ChangeAmount(int difference) const
{
	m_pCounterCp->ChangeAmount(difference);
}

void PointsCp::SetAmount(int newAmount) const
{
	m_pCounterCp->SetAmount(newAmount);
}

