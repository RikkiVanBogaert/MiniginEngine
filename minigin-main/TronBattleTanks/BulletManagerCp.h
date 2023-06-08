#pragma once
#include <glm/vec2.hpp>

#include "BaseComponent.h"

class BulletManagerCp final : public dae::ComponentBase
{
public:
	BulletManagerCp(dae::GameObject* owner);

	void Update(float deltaTime) override;
	void Shoot( const glm::vec2& vel, bool playerBullet = true);

private:
	float m_Timer{};
	bool m_HasShot{};

};

