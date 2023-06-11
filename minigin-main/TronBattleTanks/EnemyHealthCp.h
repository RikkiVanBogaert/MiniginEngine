#pragma once
#include <memory>

#include "CounterCp.h"

class UIPointsCp;
class UILivesCp;

namespace dae
{
	class GameObject;
	class CounterCp;
}

class EnemyHealthCp final : public dae::ComponentBase
{
public:
	EnemyHealthCp(dae::GameObject* owner, int startAmount);

	void ChangeAmount(int difference) const;
	void SetAmount(int newHealth) const;
	int GetAmount() const { return m_pCounterCp->GetAmount(); }

private:
	std::unique_ptr<dae::CounterCp> m_pCounterCp;
};

