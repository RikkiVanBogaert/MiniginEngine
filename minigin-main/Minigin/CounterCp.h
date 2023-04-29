#pragma once
#include "BaseComponent.h"
#include <string>

namespace dae
{

	class CounterCp : public ComponentBase
	{
	public:
		CounterCp(GameObject* owner, int startAmount);
		//virtual ~CounterCp();

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
			CounterCp(owner, startAmount) {};
		//virtual ~HealthCp();
	};

	class PointsCp final : public CounterCp
	{
	public:
		PointsCp(GameObject* owner, int startAmount) :
			CounterCp(owner, startAmount) {};
	};
}
