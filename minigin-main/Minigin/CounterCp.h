#pragma once
#include "BaseComponent.h"

namespace dae
{

	class CounterCp : public ComponentBase
	{
	public:
		CounterCp(GameObject* owner, int startAmount);
		
		virtual void ChangeAmount(int difference);
		virtual void SetAmount(int newAmount);
		int GetAmount() const;

	protected:
		int GetCounter() const { return m_Counter; }

	private:
		int m_Counter{};

	};

}
