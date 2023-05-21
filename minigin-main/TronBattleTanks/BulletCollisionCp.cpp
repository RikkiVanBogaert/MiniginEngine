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

BulletCollisionCp::BulletCollisionCp(dae::GameObject* owner):
ComponentBase(owner)
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

void BulletCollisionCp::GetHit(dae::GameObject* shooter)
{
	//Victim lives
	auto healthCp = m_pOwner->GetComponent<HealthCp>();
	healthCp->ChangeAmount(-1);
	if (auto livesText = GetComponentInScene<dae::UILivesCp>(m_pOwner->GetScene(), m_pOwner->GetTag()))
	{
		const std::string text = std::to_string(healthCp->GetAmount());
		livesText->SetValueText(text);
	}

	if (healthCp->GetAmount() > 0) return;

	//Shooter points
	if (!shooter->GetComponent<PointsCp>()) return;

	const auto shooterPoints = shooter->GetComponent<PointsCp>();
	shooterPoints->ChangeAmount(100);
	if (auto pointsText = GetComponentInScene<dae::UIPointsCp>(m_pOwner->GetScene(), shooter->GetTag()))
	{
		const std::string text = std::to_string(shooterPoints->GetAmount());
		pointsText->SetValueText(text);
	}
	
}
