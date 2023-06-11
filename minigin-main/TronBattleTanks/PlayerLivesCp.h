#pragma once
#include <memory>

#include "BaseComponent.h"
#include "CounterCp.h"

class UILivesCp;

namespace dae
{
	class GameObject;
}

class PlayerLivesCp final : public dae::ComponentBase
{
public:
	PlayerLivesCp(dae::GameObject* owner, int startAmount) :
		dae::ComponentBase(owner),
		m_pCounterCp(std::make_unique<dae::CounterCp>(owner, startAmount)) {}

	void ChangeAmount(int difference) const;
	void SetAmount(int newHealth) const;
	int GetAmount() const { return m_pCounterCp->GetAmount(); }
	dae::CounterCp* GetCounter() const { return m_pCounterCp.get(); }

	UILivesCp* GetUILives() const { return m_pUILivesCp; }
	void SetUILivesCp(UILivesCp* pUILives) { m_pUILivesCp = pUILives; }

private:
	std::unique_ptr<dae::CounterCp> m_pCounterCp;
	UILivesCp* m_pUILivesCp{};
};
