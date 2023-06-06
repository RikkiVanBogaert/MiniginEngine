#pragma once
#include "DerCounterCps.h"
#include "Observers.h"

namespace dae
{
	class GameObject;
}

class LivesObserver final : public dae::Observer
{
public:
	LivesObserver(dae::GameObject* owner, int startAmount = 3):
	m_Lives(startAmount)
	{}

	virtual void ChangeAmount(int difference);
	//virtual void SetAmount(int newHealth);

private:
	int m_Lives{};
};
