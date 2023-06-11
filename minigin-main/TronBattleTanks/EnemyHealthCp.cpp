#include "EnemyHealthCp.h"

#include "GameObject.h"
#include "UICp.h"


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
