#pragma once
#include <glm/vec2.hpp>

#include "BaseComponent.h"

class MoveCp final : public dae::ComponentBase
{
public:
	MoveCp(dae::GameObject* owner, float speed);

	void Update(float deltaTime) override;
	void Move(const glm::vec2& dir);

private:
	const float m_Speed;
	float m_DeltaT{};
};

