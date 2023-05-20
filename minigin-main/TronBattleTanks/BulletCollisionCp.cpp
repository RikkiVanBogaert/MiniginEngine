#include "BulletCollisionCp.h"

#include "BulletCp.h"
#include "CollisionCp.h"
#include "CounterCp.h"
#include "GameHelpers.h"
#include "GameObject.h"
#include "Scene.h"
#include "TextComponent.h"
#include "UICp.h"

BulletCollisionCp::BulletCollisionCp(dae::GameObject* owner):
ComponentBase(owner)
{
	m_pCollisionCp = m_pOwner->GetComponent<CollisionCp>();
	//m_pHealthCp = m_pOwner->GetComponent<dae::HealthCp>();
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
	auto healthCp = m_pOwner->GetComponent<dae::HealthCp>();
	healthCp->ChangeAmount(-1);

	if (!shooter->GetComponent<dae::PointsCp>()) return;

	const auto shooterPoints = shooter->GetComponent<dae::PointsCp>();
	shooterPoints->ChangeAmount(1);

	if (auto shooterPointsText = GetGameObject(m_pOwner->GetScene(), shooter->GetTag()))
	{
		if (auto pointsText = shooterPointsText->GetComponent<dae::UICp>())
		{
			const std::string text = pointsText->GetBeginText() + std::to_string(shooterPoints->GetAmount());
			pointsText->SetText(text);
		}
	}
}
