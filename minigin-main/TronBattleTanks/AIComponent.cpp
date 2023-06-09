#include "AIComponent.h"

#include "GameHelpers.h"
#include "GameObject.h"
#include "PlayerManager.h"
#include "BulletManagerCp.h"
#include "CollisionCp.h"
#include "MoveCp.h"

AIComponent::AIComponent(dae::GameObject* owner):
	ComponentBase(owner),
	m_ShootTime{3}
{
}

void AIComponent::Init()
{
	if (m_HasInit) return;
	m_pPlayers = PlayerManager::GetInstance().GetPlayers();
	m_pLevelCollision = GetComponentInScene<CollisionCp>(m_pOwner->GetScene(), "Level");
	m_pBulletManager = m_pOwner->GetComponent<BulletManagerCp>();
	m_HasInit = true;
}

void AIComponent::Update(float deltaTime)
{
	Init();

	GetClosestPlayer();
	glm::vec2 bulletDir{};
	if(PlayerInSight(bulletDir) && !m_HasShot)
	{
		m_pBulletManager->Shoot(bulletDir, false); 
		m_HasShot = true;
	}
	GoToPlayer(deltaTime);

	UpdateShootTimer(deltaTime);
}


void AIComponent::UpdateShootTimer(float deltaTime)
{
	if (!m_HasShot) return;

	m_ShootTimer += deltaTime;

	if(m_ShootTimer >= m_ShootTime)
	{
		m_ShootTimer = 0;
		m_HasShot = false;
	}
}

bool AIComponent::PlayerInSight(glm::vec2& bulletDir) const
{
	const glm::vec2 start{ m_pClosestPlayer->GetWorldTransform() };
	glm::vec2 end{ m_pOwner->GetWorldTransform() };
	const float playerSize{ m_pClosestPlayer->GetSize().x / 2 };
	const glm::vec2 tankMidPos{ start.x + playerSize / 2, start.y + playerSize / 2 };

	//Straight line
	if (!(tankMidPos.x > end.x && tankMidPos.x < end.x + playerSize)
		&& !(tankMidPos.y > end.y && tankMidPos.y < end.y + playerSize))
		return false;

	const auto playerPos = m_pClosestPlayer->GetRelativeTransform();
	const auto playerDir = playerPos - m_pOwner->GetRelativeTransform();
	const float dirLength = sqrtf(playerDir.x * playerDir.x + playerDir.y * playerDir.y);
	const glm::vec2 playerDirNormalized = { playerDir.x / dirLength, playerDir.y / dirLength };
	constexpr float bulletSpeed{ 250 };
	bulletDir = { playerDirNormalized.x * bulletSpeed, playerDirNormalized.y * bulletSpeed };
	return true;

	//Still need to check whether there is wall between enemy and player---
	//if(!m_pLevelCollision->CollisionHit(m_pOwner, playerPos))
}

void AIComponent::GoToPlayer(float) const
{

	constexpr glm::vec2 up{ 0,-1 };
	constexpr glm::vec2 down{ 0,1 };
	constexpr glm::vec2 left{ -1, 0 };
	constexpr glm::vec2 right{ 1, 0 };

	const glm::vec2 playerPos{ m_pClosestPlayer->GetWorldTransform() };
	const glm::vec2 ownerPos{ m_pOwner->GetWorldTransform() };


	if (playerPos.y < ownerPos.y)
	{
		if (!m_pLevelCollision->CollisionHit(m_pOwner, up))
		{
			m_pOwner->GetComponent<MoveCp>()->Move(up);
		}
	}
	else
	{
		if (!m_pLevelCollision->CollisionHit(m_pOwner, up))
		{
			m_pOwner->GetComponent<MoveCp>()->Move(down);
		}
	}

	if (playerPos.x < ownerPos.x)
	{
		if (!m_pLevelCollision->CollisionHit(m_pOwner, left))
		{
			m_pOwner->GetComponent<MoveCp>()->Move(left);
		}
	}
	else
	{
		if (!m_pLevelCollision->CollisionHit(m_pOwner, right))
		{
			m_pOwner->GetComponent<MoveCp>()->Move( right);
		}
	}
	
}

void AIComponent::GetClosestPlayer()
{
	//check closest player
	float closestDistance{ INFINITY };

	for (auto p : m_pPlayers)
	{
		if (!p->GetScene()->IsActive()) continue;

		float d = distance(p->GetWorldTransform(), m_pOwner->GetWorldTransform());
		if (d < closestDistance)
		{
			closestDistance = d;
			m_pClosestPlayer = p.get();
		}
	}
}


