#include "AIComponent.h"

#include "GameHelpers.h"
#include "GameObject.h"
#include "Scene.h"
#include "PlayerManager.h"
#include "BulletManagerCp.h"
#include "CollisionCp.h"

AIComponent::AIComponent(dae::GameObject* owner):
	ComponentBase(owner),
	m_ShootTime{3}
{
}

void AIComponent::Update(float deltaTime)
{
	Init();

	if (m_HasShot)
	{
		UpdateShootTimer(deltaTime);
		return;
	}

	glm::vec2 bulletDir{};
	if(PlayerInSight(bulletDir))
	{
		m_pBulletManager->Shoot(bulletDir); 
		m_HasShot = true;
	}

	////else, find a way around it.
}

void AIComponent::Init()
{
	if (m_HasInit) return;
	m_pPlayers = PlayerManager::GetInstance().GetPlayers();
	m_pLevelCollision = GetComponentInScene<CollisionCp>(m_pOwner->GetScene(), "Level");
	m_pBulletManager = m_pOwner->GetComponent<BulletManagerCp>();
	m_HasInit = true;
}


void AIComponent::UpdateShootTimer(float deltaTime)
{
	m_ShootTimer += deltaTime;

	if(m_ShootTimer >= m_ShootTime)
	{
		m_ShootTimer = 0;
		m_HasShot = false;
	}
}

bool AIComponent::PlayerInSight(glm::vec2& bulletDir)
{
	for (auto p : m_pPlayers)
	{
		if (p->NeedsDeleting()) continue;

		const glm::vec2 start{ p->GetWorldTransform() };
		glm::vec2 end{ m_pOwner->GetWorldTransform() };
		const float playerSize{ p->GetSize().x / 2 };
		const glm::vec2 tankMidPos{ start.x + playerSize / 2, start.y + playerSize / 2 };

		//Straight line
		if (!(tankMidPos.x > end.x && tankMidPos.x < end.x + playerSize)
			&& !(tankMidPos.y > end.y && tankMidPos.y < end.y + playerSize))
			return false;

		const auto playerPos = p->GetRelativeTransform();
		const auto playerDir = playerPos - m_pOwner->GetRelativeTransform();
		const float dirLength = sqrtf(playerDir.x * playerDir.x + playerDir.y * playerDir.y);
		const glm::vec2 playerDirNormalized = { playerDir.x / dirLength, playerDir.y / dirLength };
		constexpr float bulletSpeed{ 250 };
		bulletDir = { playerDirNormalized.x * bulletSpeed, playerDirNormalized.y * bulletSpeed };
		return true;

		//Still need to check whether there is wall between enemy and player---
		//if(!m_pLevelCollision->CollisionHit(m_pOwner, playerPos))
	}
	return false;
}
