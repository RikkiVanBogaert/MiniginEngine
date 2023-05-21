#pragma once
#include "BaseComponent.h"


class HealthCp;

class CollisionCp;

class BulletCollisionCp final : public dae::ComponentBase
{
public:
	BulletCollisionCp(dae::GameObject* owner, int pointsGivenOnKill = 100);

	void Update(float deltaTime) override;

private:
	CollisionCp* m_pCollisionCp;
	const int m_PointsGivenOnKill;

	void GetHit(dae::GameObject* shooter);
};

