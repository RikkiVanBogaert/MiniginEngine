#pragma once
#include <memory>

#include "BaseComponent.h"
#include "CounterCp.h"

namespace dae
{
	class UIPointsCp;
}

class PointsCp final : public dae::ComponentBase
{
public:
	PointsCp(dae::GameObject* owner, int startAmount) :
		ComponentBase(owner),
		m_pCounterCp(std::make_unique<dae::CounterCp>(owner, startAmount)) {}

	dae::CounterCp* GetCounter() const { return m_pCounterCp.get(); }

	dae::UIPointsCp* GetUIPoints() const { return m_pUIPointsCp; }
	void SetUIPointsCp(dae::UIPointsCp* pUILives) { m_pUIPointsCp = pUILives; }

private:
	std::unique_ptr<dae::CounterCp> m_pCounterCp;
	dae::UIPointsCp* m_pUIPointsCp{};
};
