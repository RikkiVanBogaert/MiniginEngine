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

	class HealthCp final : public CounterCp
	{
	public:
		HealthCp(GameObject* owner, int startAmount) : 
			CounterCp(owner, startAmount) {}

		virtual void ChangeAmount(int difference);
		virtual void SetAmount(int newHealth);

	};

	class PointsCp final : public CounterCp
	{
	public:
		PointsCp(GameObject* owner, int startAmount) :
			CounterCp(owner, startAmount) {}
	};
}
