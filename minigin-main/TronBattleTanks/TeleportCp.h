#pragma once
#include <vector>
#include <glm/vec2.hpp>

#include "BaseComponent.h"

class CollisionCp;

class TeleportCp final : public dae::ComponentBase
{
public:
	TeleportCp(dae::GameObject* owner, const std::vector<int>& teleportPlaces);

	void Update(float deltaTime) override;

private:
	CollisionCp* m_pCollisionCp;
	const std::vector<int> m_TeleportPlaceIdxs{};

	glm::vec2 GetRandomPos() const;
};

