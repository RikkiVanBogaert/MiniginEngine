#include "BulletCp.h"
#include "GameObject.h"
#include "CollisionCp.h"
#include "GameHelpers.h"

BulletCp::BulletCp(dae::GameObject* owner,dae::GameObject* shooter, const glm::vec2& vel):
ComponentBase(owner),
m_pShooter(shooter),
m_Velocity(vel)
{
	m_pCollisionCp = GetGameObject(m_pOwner->GetScene(), "Level")->GetComponent<CollisionCp>();
}

void BulletCp::Update(float deltaTime)
{
	const auto newPos = m_pOwner->GetRelativeTransform() + m_Velocity * deltaTime;
	m_pOwner->SetRelativePos(newPos);

	if (!m_pCollisionCp->CollisionHit(m_pOwner, m_Velocity)) return;

	m_Velocity *= -1;

	++m_AmountBounces;

	if (m_AmountBounces >= 5) m_pOwner->MarkForDeletion();
}

dae::GameObject* BulletCp::GetShooter() const
{
	return m_pShooter;
}
