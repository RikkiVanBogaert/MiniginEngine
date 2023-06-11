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
	PlayerLivesCp(dae::GameObject* owner, int startAmount);

	void ChangeAmount(int difference) const;
	void SetAmount(int newHealth) const;
	int GetAmount() const { return m_pCounterCp->GetAmount(); }
	
	UILivesCp* GetUILives() const { return m_pUILivesCp; }
	void SetUILivesCp(UILivesCp* pUILives) { m_pUILivesCp = pUILives; }

private:
	std::unique_ptr<dae::CounterCp> m_pCounterCp;
	UILivesCp* m_pUILivesCp{};
};
