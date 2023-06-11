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
	m_pCollisionCp = GetOwner()->GetComponent<CollisionCp>();
}

void BulletCollisionCp::Update(float )
{
	BulletCp* bulletCp{};
	for(auto o : GetOwner()->GetScene()->GetGameObjects())
	{
		bulletCp = o->GetComponent<BulletCp>();
		if (!bulletCp) continue;
		if(o->GetTag() == GetOwner()->GetTag()) continue;
		

		if(m_pCollisionCp->CollisionHit(o.get(), bulletCp->GetVelocity()))
		{
			//bug: recognizer and blueTank can kill eachother - fixed
			//check if not 2 enemies
			if (o->GetTag() == "BlueEnemy" && GetOwner()->GetTag() == "Recognizer") return;
			if (o->GetTag() == "Recognizer" && GetOwner()->GetTag() == "BlueEnemy") return;

			o->MarkForDeletion();
			GetHit(bulletCp->GetShooter());
		}
	}
	//bulletCp = nullptr;
}

void BulletCollisionCp::GetHit(dae::GameObject* gun) const
{
	//Victim lives
	const auto healthCp = GetOwner()->GetComponent<HealthCp>();
	healthCp->ChangeAmount(-1);
	if (const auto livesCp = GetComponentInScene<dae::UILivesCp>(GetOwner()->GetScene(), GetOwner()->GetTag()))
	{
		const auto event = std::make_shared<PlayerHitEvent>();
		livesCp->UpdateSubject(event);
	}

	//bug: killing enemy when getting killed

	//Shooter points
	if(!gun->GetParent()) return;
	if(!gun->GetParent()->GetComponent<PointsCp>()) return;

	if (healthCp->GetAmount() > 0) return;

	if (const auto pointsText = GetComponentInScene<dae::UIPointsCp>(GetOwner()->GetScene()))
	{
		if(GetOwner()->GetTag() == "BlueEnemy")
		{
			const auto event = std::make_shared<BlueTankKilledEvent>();
			pointsText->UpdateSubject(event);
		}
		else if (GetOwner()->GetTag() == "Recognizer")
		{
			const auto event = std::make_shared<RecognizerKilledEvent>();
			pointsText->UpdateSubject(event);
		}
	}
	
}
