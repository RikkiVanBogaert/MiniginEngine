#pragma once
#include <memory>
#include "GameObject.h"

class RedTank final : public GameObject
{
public:
	RedTank();
	virtual ~RedTank() {};

	virtual void Update(float deltaTime) override;

private:
	std::shared_ptr<GameObject> m_pGun;
	float m_GunAngle{};

	void CheckOverlap();
	void RotateGun(float deltaTime);
	void rotateObject(float& x, float& y, float angle);
};

class BlueTank final : public GameObject
{
public:
	BlueTank();
	virtual ~BlueTank() {};

	virtual void Update(float deltaTime) override;

private:
	std::shared_ptr<GameObject> m_pGun;
	float m_GunAngle{};

	void CheckOverlap();
};

