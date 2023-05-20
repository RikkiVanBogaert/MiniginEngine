#pragma once
#include "CounterCp.h"

namespace dae
{
	class GameObject;
	class CounterCp;
}

class HealthCp  : public dae::CounterCp
{
public:
	HealthCp(dae::GameObject* owner, int startAmount) :
		CounterCp(owner, startAmount) {}

	virtual void ChangeAmount(int difference);
	virtual void SetAmount(int newHealth);

};

class LivesCp final : public HealthCp
{
public:
	LivesCp(dae::GameObject* owner, int startAmount) :
		HealthCp(owner, startAmount) {}

	virtual void ChangeAmount(int difference);
	//virtual void SetAmount(int newHealth);

};

class PointsCp final : public dae::CounterCp
{
public:
	PointsCp(dae::GameObject* owner, int startAmount) :
		dae::CounterCp(owner, startAmount) {}
};
