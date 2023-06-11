#pragma once
#include "BaseComponent.h"

namespace dae
{

	class CounterCp final : public ComponentBase
	{
	public:
		CounterCp(GameObject* owner, int startAmount);
		
		void ChangeAmount(int difference);
		void SetAmount(int newAmount);
		int GetAmount() const;
		int GetCounter() const { return m_Counter; }

	private:
		int m_Counter{};

	};

}
