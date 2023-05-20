#pragma once
#include <glm/vec2.hpp>

#include "BaseComponent.h"

class CollisionCp;

class BulletCp final : public dae::ComponentBase
{
public:
	BulletCp(dae::GameObject* owner, dae::GameObject* shooter, const glm::vec2& vel);

	void Update(float deltaTime) override;
	dae::GameObject* GetShooter() const;
	glm::vec2 GetVelocity() const { return m_Velocity; }

private:
	dae::GameObject* m_pShooter;
	glm::vec2 m_Velocity;
	CollisionCp* m_pCollisionCp;
	int m_AmountBounces{};
};

