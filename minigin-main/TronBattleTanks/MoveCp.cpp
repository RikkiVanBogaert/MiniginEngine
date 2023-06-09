#include "MoveCp.h"

#include "GameHelpers.h"
#include "GameObject.h"
#include "GridCp.h"

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

	glm::vec2 pos = m_pOwner->GetRelativeTransform();
	const auto normalizedDir = normalize(dir);

	pos.x +=  normalizedDir.x * m_Speed * m_DeltaT;
	pos.y += normalizedDir.y * m_Speed * m_DeltaT;

	m_pOwner->SetRelativePos(pos);
}

