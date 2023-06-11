#include "AIRecognizerCp.h"

#include "GameHelpers.h"
#include "MoveCp.h"
#include "GameManager.h"
#include "BulletManagerCp.h"
#include "CollisionCp.h"

#include <glm/glm.hpp>

AIRecognizerCp::AIRecognizerCp(dae::GameObject* owner) :
	ComponentBase(owner),
	m_State(std::make_shared<WanderState>(this))
{}


void AIRecognizerCp::Init()
{
	if (m_HasInit) return;
	m_pPlayers = GameManager::GetInstance().GetPlayers();
	m_pLevelCollision = GetComponentInScene<CollisionCp>(GetOwner()->GetScene(), "Level");
	m_pBulletManager = GetOwner()->GetComponent<BulletManagerCp>();
	m_HasInit = true;
}

void AIRecognizerCp::Update(float deltaTime)
{
	Init();
	m_State->Update(GetOwner(), deltaTime, m_pPlayers, m_pLevelCollision, m_pBulletManager);
}

void AIRecognizerCp::SetState(const std::shared_ptr<RecognizerState>& newState)
{
	m_State = newState;
}

bool RecognizerState::PlayerInSight(dae::GameObject* gameObject, const std::vector<std::shared_ptr<dae::GameObject>>& players)
{
	for (const auto& p : players)
	{
		const glm::vec2 playerPos{ p->GetWorldTransform() };
		const glm::vec2 pos{ gameObject->GetWorldTransform() };
		const float playerSize{ p->GetSize().x / 2 };
		const glm::vec2 tankMidPos{ playerPos.x + playerSize / 2, playerPos.y + playerSize / 2 };

		//Straight line
		if ((tankMidPos.x > pos.x && tankMidPos.x < pos.x + playerSize)
			|| (tankMidPos.y > pos.y && tankMidPos.y < pos.y + playerSize))
		{
			m_ToPlayer = glm::normalize(playerPos - pos);
			return true;
		}
	}
	return false;

}

void WanderState::Update(dae::GameObject* gameObject, float ,
                         std::vector<std::shared_ptr<dae::GameObject>> players, CollisionCp* levelCollision, BulletManagerCp* )
{
	if (!levelCollision->CollisionHit(gameObject, m_Direction))
	{
		gameObject->GetComponent<MoveCp>()->Move(m_Direction);
	}

	//check for open side paths
	auto sideDir = abs(m_Direction);
	sideDir.x -= 1;
	sideDir.y -= 1;

	if (!levelCollision->CollisionHit(gameObject, sideDir) &&
		rand() % 3 == 0)
	{
		m_Direction = sideDir;
	}
	if (!levelCollision->CollisionHit(gameObject, -sideDir) &&
		rand() % 3 == 0)
	{
		m_Direction = -sideDir;
	}

	if(PlayerInSight(gameObject, players))
	{
		GetAICp()->SetState(std::make_shared<AttackState>(GetAICp(), GetToPlayer()));
	}
}

void AttackState::Update(dae::GameObject* gameObject, float deltaTime,
                         std::vector<std::shared_ptr<dae::GameObject>> players, CollisionCp* , BulletManagerCp* bulletManager)
{
	if (!m_HasShot)
	{
		bulletManager->Shoot(m_ShootDirection, false);
		m_HasShot = true;
	}
	UpdateShootTimer(deltaTime);

	if (!PlayerInSight(gameObject, players))
	{
		GetAICp()->SetState(std::make_shared<WanderState>(GetAICp()));
	}
}

void AttackState::UpdateShootTimer(float deltaTime)
{
	if (!m_HasShot) return;

	m_ShootTimer += deltaTime;

	if (m_ShootTimer >= m_ShootDelay)
	{
		m_ShootTimer = 0;
		m_HasShot = false;
	}
}


