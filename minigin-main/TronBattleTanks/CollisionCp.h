#pragma once
#include <vector>
#include <glm/vec2.hpp>

#include "BaseComponent.h"

class CollisionCp final : public dae::ComponentBase
{
public:
	CollisionCp(dae::GameObject* owner);

	void SetColliders(std::vector<dae::GameObject*> colliders);
	void AddCollider(dae::GameObject* collider);

	bool CollisionHit(dae::GameObject* object, const glm::vec2& dir);

private:
	std::vector<dae::GameObject*> m_pColliders;
};

