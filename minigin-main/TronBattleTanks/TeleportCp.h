#pragma once
#include <glm/vec2.hpp>

#include "BaseComponent.h"

class CollisionCp;

class TeleportCp final : public dae::ComponentBase
{
public:
	TeleportCp(dae::GameObject* owner);

	void Update(float deltaTime) override;

private:
	CollisionCp* m_pCollisionCp;

	glm::vec2 GetRandomPos();
};

