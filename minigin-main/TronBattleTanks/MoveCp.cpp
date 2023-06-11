#include "MoveCp.h"

#include "GameObject.h"

#include <glm/glm.hpp>

MoveCp::MoveCp(dae::GameObject* owner, float speed):
ComponentBase(owner),
m_Speed(speed)
{}

void MoveCp::Update(float deltaTime)
{
	m_DeltaT = deltaTime;
}

void MoveCp::Move(const glm::vec2& dir) const
{

	glm::vec2 pos = GetOwner()->GetRelativeTransform();
	const auto normalizedDir = normalize(dir);

	pos.x += normalizedDir.x * m_Speed * m_DeltaT;
	pos.y += normalizedDir.y * m_Speed * m_DeltaT;

	GetOwner()->SetRelativePos(pos);
}

