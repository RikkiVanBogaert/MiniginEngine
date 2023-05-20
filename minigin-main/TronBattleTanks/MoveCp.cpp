#include "MoveCp.h"
#include "GameObject.h"

MoveCp::MoveCp(dae::GameObject* owner):
ComponentBase(owner)
{}

void MoveCp::Move(float deltaT, const glm::vec2 dir)
{
	glm::vec2 pos = m_pOwner->GetRelativeTransform();
	pos.x += dir.x * deltaT;
	pos.y += dir.y * deltaT;

	m_pOwner->SetRelativePos(pos);
}

