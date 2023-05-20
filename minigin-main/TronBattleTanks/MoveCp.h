#pragma once
#include <glm/vec2.hpp>

#include "BaseComponent.h"

class MoveCp final : public dae::ComponentBase
{
public:
	MoveCp(dae::GameObject* owner);

	void Move(float deltaT, const glm::vec2 dir);
};

