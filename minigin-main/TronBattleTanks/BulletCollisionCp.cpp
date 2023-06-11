#include "BulletCollisionCp.h"

#include "BulletCp.h"
#include "CollisionCp.h"
#include "EnemyHealthCp.h"
#include "PlayerLivesCp.h"
#include "PointsCp.h"
#include "GameHelpers.h"
#include "GameObject.h"
#include "Scene.h"
#include "UICp.h"
#include "GameObserverEvents.h"

BulletCollisionCp::BulletCollisionCp(dae::GameObject* owner, int pointsGivenOnKill):
ComponentBase(owner),
m_pCollisionCp(GetOwner()->GetComponent<CollisionCp>()),
m_PointsGivenOnKill(pointsGivenOnKill)
{}

void BulletCollisionCp::Update(float )
{
	BulletCp* bulletCp{};
	for (auto o : GetOwner()->GetScene()->GetGameObjects())
	{
		bulletCp = o->GetComponent<BulletCp>();
		if (!bulletCp) continue;
		if (o->GetTag() == GetOwner()->GetTag()) continue;


		if (m_pCollisionCp->CollisionHit(o.get(), bulletCp->GetVelocity()))
		{
			//check if not 2 enemies
			if (o->GetTag() == "BlueEnemy" && GetOwner()->GetTag() == "Recognizer") return;
			if (o->GetTag() == "Recognizer" && GetOwner()->GetTag() == "BlueEnemy") return;

			o->MarkForDeletion();
			GetHit(bulletCp->GetShooter());
		}
	}
}

void BulletCollisionCp::GetHit(const dae::GameObject* gun) const
{
	//Victim lives
	if (const auto livesCp = GetOwner()->GetComponent<PlayerLivesCp>())
	{
		//Player
		const auto pUILives = livesCp->GetUILives();

		const auto event = std::make_shared<PlayerHitEvent>();
		pUILives->UpdateSubject(event);
	}
	else
	{
		//AI
		const auto healthCp = GetOwner()->GetComponent<EnemyHealthCp>();
		healthCp->ChangeAmount(-1);

		//AI not dead
		if (healthCp->GetAmount() > 0) return;
	}

	//Shooter points
	if(!gun->GetParent()) return;
	if(!gun->GetParent()->GetComponent<PointsCp>()) return;


	if (const auto pointsCp = gun->GetParent()->GetComponent<PointsCp>())
	{
		const auto UIPoints = pointsCp->GetUIPoints();
		if(GetOwner()->GetTag() == "BlueEnemy")
		{
			const auto event = std::make_shared<BlueTankKilledEvent>();
			UIPoints->UpdateSubject(event);
		}
		else if (GetOwner()->GetTag() == "Recognizer")
		{
			const auto event = std::make_shared<RecognizerKilledEvent>();
			UIPoints->UpdateSubject(event);
		}
	}
	
}
