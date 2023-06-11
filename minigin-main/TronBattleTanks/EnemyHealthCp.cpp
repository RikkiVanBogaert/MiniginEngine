#include "EnemyHealthCp.h"

#include "GameObject.h"
#include "UICp.h"


EnemyHealthCp::EnemyHealthCp(dae::GameObject* owner, int startAmount):
	ComponentBase(owner),
	m_pCounterCp(std::make_unique<dae::CounterCp>(owner, startAmount)) {}

void EnemyHealthCp::ChangeAmount(int difference) const
{
	m_pCounterCp->ChangeAmount(difference);

	if (m_pCounterCp->GetAmount() > 0) return;

	GetOwner()->MarkForDeletion();
}

void EnemyHealthCp::SetAmount(int newHealth) const
{
	m_pCounterCp->SetAmount(newHealth);

	if (m_pCounterCp->GetAmount() > 0) return;

	GetOwner()->MarkForDeletion();
}
