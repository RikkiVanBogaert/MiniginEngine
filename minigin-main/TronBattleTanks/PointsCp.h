#pragma once
#include <memory>

#include "BaseComponent.h"
#include "CounterCp.h"


class UIPointsCp;

class PointsCp final : public dae::ComponentBase
{
public:
	PointsCp(dae::GameObject* owner, int startAmount);

	void ChangeAmount(int difference) const;
	void SetAmount(int newAmount) const;
	int GetAmount() const { return m_pCounterCp->GetAmount(); }

	UIPointsCp* GetUIPoints() const { return m_pUIPointsCp; }
	void SetUIPointsCp(UIPointsCp* pUILives) { m_pUIPointsCp = pUILives; }

private:
	std::unique_ptr<dae::CounterCp> m_pCounterCp;
	UIPointsCp* m_pUIPointsCp{};
};
