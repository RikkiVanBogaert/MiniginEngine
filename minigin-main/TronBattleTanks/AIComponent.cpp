#include "AIComponent.h"

#include "GameObject.h"
#include "Scene.h"
#include "Tank.h"
#include "Level.h"

AIComponent::AIComponent(dae::GameObject* owner)
{
	m_pOwner = owner;

	m_pAiOwner = dynamic_cast<BlueTank*>(owner);
	FindPlayer();
	FindLevel();
	//if this doesnt work, do this in update if m_pLevel == nullptr
}

void AIComponent::Update(float)
{
	if (!m_pPlayer || m_pPlayer->NeedsDeleting()) return;

	auto playerDir = m_pPlayer->GetRelativeTransform() - m_pOwner->GetRelativeTransform();

	//pas playerDir into a level function, which checks wether or not the dir goes through a wall.
	//if it doesnt, shoot in that direction.
	if(!m_pLevel->HitWall(m_pAiOwner->GetRelativeTransform(), m_pPlayer->GetRelativeTransform()))
	{
		m_pAiOwner->ShootBullet(playerDir);
	}

	//else, find a way around it.
}

void AIComponent::FindPlayer()
{
	for (auto& o : m_pOwner->GetScene()->GetGameObjects())
	{
		if (!dynamic_cast<RedTank*>(o.get())) continue;

		m_pPlayer = dynamic_cast<RedTank*>(o.get());
	}
}

//Make helper function which finds an object of a certain type in the scene

void AIComponent::FindLevel()
{
	for (auto& o : m_pOwner->GetScene()->GetGameObjects())
	{
		if (!dynamic_cast<Level*>(o.get())) continue;

		m_pLevel = dynamic_cast<Level*>(o.get());
	}
}
