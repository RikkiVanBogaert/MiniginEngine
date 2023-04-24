#pragma once
#include <memory>
#include "GameObject.h"

class Tank final : public GameObject
{
public:
	Tank();
	virtual ~Tank() {};

	virtual void Update(float deltaTime) override;

private:
	std::shared_ptr<GameObject> m_pGun;
	float m_GunAngle{};

	void CheckOverlap();
	void RotateGun(float deltaTime);
	void rotateObject(float& x, float& y, float angle);
};

