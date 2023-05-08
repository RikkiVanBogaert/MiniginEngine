#pragma once
#include "GameObject.h"
#include "CounterCp.h"

#include <memory>


class Tank : public dae::GameObject
{
public:
	Tank() = default;

	virtual void Update(float deltaTime) override;

protected:
	std::shared_ptr<GameObject> m_pGun;
	std::shared_ptr<dae::HealthCp> m_pHealth;

private:
	void CheckOverlap();
	virtual void GetHit() = 0;
};

class RedTank final : public Tank
{
public:
	RedTank();

private:
	virtual void GetHit() override;
};

class BlueTank final : public Tank
{
public:
	BlueTank();

private:
	virtual void GetHit() override;

};

