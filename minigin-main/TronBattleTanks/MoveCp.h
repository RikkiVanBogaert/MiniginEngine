#pragma once
#include <glm/vec2.hpp>

#include "BaseComponent.h"

class GridCp;

class MoveCp final : public dae::ComponentBase
{
public:
	MoveCp(dae::GameObject* owner, float speed);

	void Update(float deltaTime) override;
	void Move(const glm::vec2& dir) const;

private:
	const float m_Speed;
	float m_DeltaT{};
};

