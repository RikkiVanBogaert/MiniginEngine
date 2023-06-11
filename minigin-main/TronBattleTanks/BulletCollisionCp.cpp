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
#include "GameObserverEvents.h"

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

void BulletCollisionCp::GetHit(dae::GameObject* gun) const
{
	//Victim lives
	const auto healthCp = m_pOwner->GetComponent<HealthCp>();
	healthCp->ChangeAmount(-1);
	if (const auto livesCp = GetComponentInScene<dae::UILivesCp>(m_pOwner->GetScene(), m_pOwner->GetTag()))
	{
		const auto event = std::make_shared<PlayerHitEvent>();
		livesCp->UpdateSubject(event);
	}

	//Shooter points
	//bug: killing enemy when getting killed
	if(!gun->GetParent()) return;
	if(!gun->GetParent()->GetComponent<PointsCp>()) return;

	if (healthCp->GetAmount() > 0) return;

	if (const auto pointsText = GetComponentInScene<dae::UIPointsCp>(m_pOwner->GetScene()))
	{
		if(m_pOwner->GetTag() == "BlueEnemy")
		{
			const auto event = std::make_shared<BlueTankKilledEvent>();
			pointsText->UpdateSubject(event);
		}
		else if (m_pOwner->GetTag() == "Recognizer")
		{
			const auto event = std::make_shared<RecognizerKilledEvent>();
			pointsText->UpdateSubject(event);
		}
	}
	
}
