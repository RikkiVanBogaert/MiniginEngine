#pragma once
#include "BaseComponent.h"

namespace dae
{

	class CounterCp : public ComponentBase
	{
	public:
		CounterCp(GameObject* owner, int startAmount);
		
		void ChangeAmount(int difference);
		void SetAmount(int newHealth);
		int GetAmount() const;

	private:
		int m_Counter{};

	};

	class HealthCp final : public CounterCp
	{
	public:
		HealthCp(GameObject* owner, int startAmount) : 
			CounterCp(owner, startAmount) {}

	};

	class PointsCp final : public CounterCp
	{
	public:
		PointsCp(GameObject* owner, int startAmount) :
			CounterCp(owner, startAmount) {}
	};
}
