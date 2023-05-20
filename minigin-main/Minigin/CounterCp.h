#pragma once
#include "BaseComponent.h"

namespace dae
{

	class CounterCp : public ComponentBase
	{
	public:
		CounterCp(GameObject* owner, int startAmount);
		
		virtual void ChangeAmount(int difference);
		virtual void SetAmount(int newHealth);
		int GetAmount() const;

	protected:
		int& GetCounter() { return m_Counter; }

	private:
		int m_Counter{};

	};

}
