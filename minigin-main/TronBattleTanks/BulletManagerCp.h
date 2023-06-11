#pragma once
#include <glm/vec2.hpp>

#include "BaseComponent.h"

class BulletManagerCp final : public dae::ComponentBase
{
public:
	BulletManagerCp(dae::GameObject* owner, float bulletSpeed = 200);

	void Update(float deltaTime) override;
	void Shoot( const glm::vec2& vel, bool playerBullet = true);

private:
	const float m_BulletSpeed{};
	float m_Timer{};
	bool m_HasShot{};
};

