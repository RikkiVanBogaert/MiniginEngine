#include "BulletCp.h"
#include "GameObject.h"
#include "CollisionCp.h"
#include "GameHelpers.h"

BulletCp::BulletCp(dae::GameObject* owner,dae::GameObject* shooter, const glm::vec2& vel):
ComponentBase(owner),
m_pShooter(shooter),
m_Velocity(vel)
{
	if (!GetGameObject(GetOwner()->GetScene(), "Level")) return;
	if (!GetGameObject(GetOwner()->GetScene(), "Level")->GetComponent<CollisionCp>()) return;

	m_pCollisionCp = GetGameObject(GetOwner()->GetScene(), "Level")->GetComponent<CollisionCp>();
}

void BulletCp::Update(float deltaTime)
{
	const auto newPos = GetOwner()->GetRelativeTransform() + m_Velocity * deltaTime;
	GetOwner()->SetRelativePos(newPos);

	if (!m_pCollisionCp) return;
	if (!m_pCollisionCp->CollisionHit(GetOwner(), m_Velocity)) return;

	m_Velocity *= -1;

	++m_AmountBounces;

	if (m_AmountBounces >= 5) GetOwner()->MarkForDeletion();
}

dae::GameObject* BulletCp::GetShooter() const
{
	return m_pShooter;
}
