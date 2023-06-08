#include "BulletCollisionCp.h"

#include "BulletCp.h"
#include "CollisionCp.h"
#include "CounterCp.h"
#include "DerCounterCps.h"
#include "GameHelpers.h"
#include "GameObject.h"
#include "Scene.h"
#include "TextComponent.h"
#include "UICp.h"

BulletCollisionCp::BulletCollisionCp(dae::GameObject* owner, int pointsGivenOnKill):
ComponentBase(owner),
m_PointsGivenOnKill(pointsGivenOnKill)
{
	m_pCollisionCp = m_pOwner->GetComponent<CollisionCp>();
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
			GetHit(bulletCp->GetShooter());
		}
	}
	bulletCp = nullptr;
}

void BulletCollisionCp::GetHit(dae::GameObject* shooter) const
{
	//Victim lives
	const auto healthCp = m_pOwner->GetComponent<HealthCp>();
	healthCp->ChangeAmount(-1);
	if (const auto livesCp = GetComponentInScene<dae::UILivesCp>(m_pOwner->GetScene(), m_pOwner->GetTag()))
	{
		livesCp->UpdateSubject(dae::PlayerHit);
	}

	//Shooter points
	if (!shooter->GetComponent<PointsCp>()) return;

	if (healthCp->GetAmount() > 0) return;

	if (const auto pointsText = GetComponentInScene<dae::UIPointsCp>(m_pOwner->GetScene()))
	{
		if(m_pOwner->GetTag() == "BlueEnemy")
		{
			pointsText->UpdateSubject(dae::BlueTankKilled);
		}
		else if (m_pOwner->GetTag() == "Recognizer")
		{
			pointsText->UpdateSubject(dae::RecognizerKilled);
		}
	}
	
}
