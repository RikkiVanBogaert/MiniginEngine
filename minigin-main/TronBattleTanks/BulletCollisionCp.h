#pragma once
#include "BaseComponent.h"


namespace dae
{
	class HealthCp;
}

class CollisionCp;

class BulletCollisionCp final : public dae::ComponentBase
{
public:
	BulletCollisionCp(dae::GameObject* owner);

	void Update(float deltaTime) override;

private:
	CollisionCp* m_pCollisionCp;
	dae::HealthCp* m_pHealthCp;

	void GetHit();
};

