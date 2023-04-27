#pragma once
#include <memory>
#include "GameObject.h"

class Tank : public GameObject
{
public:
	Tank() = default;
	virtual ~Tank() {};

	virtual void Update(float deltaTime) override;

protected:
	std::shared_ptr<GameObject> m_pGun;

private:
	void CheckOverlap();
};

class RedTank final : public Tank
{
public:
	RedTank();
	virtual ~RedTank() {};
};

class BlueTank final : public Tank
{
public:
	BlueTank();
	virtual ~BlueTank() {};

};

