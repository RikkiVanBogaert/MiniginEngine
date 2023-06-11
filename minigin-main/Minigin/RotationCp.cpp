#include "RotationCp.h"
#include "GameObject.h"

using namespace dae;

RotationCp::RotationCp(GameObject* owner, float rotSpeed, float radius) :
ComponentBase(owner),
	m_RotSpeed{rotSpeed},
	m_Radius{ radius },
	m_OffsetToParent{ owner->GetWorldTransform() }
{}

void RotationCp::Update(float deltaTime)
{
	//update angle
	m_Angle += m_RotSpeed * deltaTime;

	//use matrices instead
	glm::vec2 newPos{ m_OffsetToParent.x + cosf(m_Angle) * m_Radius,
		m_OffsetToParent.y + sinf(m_Angle) * m_Radius };
	GetOwner()->SetRelativePos({newPos.x, newPos.y});
}
