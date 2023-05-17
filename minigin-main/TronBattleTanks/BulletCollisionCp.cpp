#include "BulletCollisionCp.h"

#include "BulletCp.h"
#include "CollisionCp.h"
#include "CounterCp.h"
#include "GameObject.h"
#include "Scene.h"

BulletCollisionCp::BulletCollisionCp(dae::GameObject* owner):
ComponentBase(owner)
{
	m_pCollisionCp = m_pOwner->GetComponent<CollisionCp>();
	m_pHealthCp = m_pOwner->GetComponent<dae::HealthCp>();
}

void BulletCollisionCp::Update(float )
{
	BulletCp* bulletCp{};
	for(auto o : m_pOwner->GetScene()->GetGameObjects())
	{
		bulletCp = o->GetComponent<BulletCp>();
		if (!bulletCp) continue;
		if(o->GetTag() == m_pOwner->GetTag()) continue;

		if(m_pCollisionCp->CollisionHit(o.get(), bulletCp->GetVelocity()))
		{
			o->MarkForDeletion();
			GetHit();
		}
	}
	bulletCp = nullptr;
}

void BulletCollisionCp::GetHit()
{
	m_pHealthCp->ChangeAmount(-1);
}
