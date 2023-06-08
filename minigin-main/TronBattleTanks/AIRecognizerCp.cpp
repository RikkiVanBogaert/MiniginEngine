#include "AIRecognizerCp.h"

#include "GameHelpers.h"
#include "MoveCp.h"
#include "PlayerManager.h"
#include "BulletManagerCp.h"
#include "CollisionCp.h"

AIRecognizerCp::AIRecognizerCp(dae::GameObject* owner) :
	ComponentBase(owner),
	m_State(std::make_shared<WanderState>(this))
{
	//m_State->SetAiCpState(this);
}


void AIRecognizerCp::Init()
{
	if (m_HasInit) return;
	m_pPlayers = PlayerManager::GetInstance().GetPlayers();
	m_pLevelCollision = GetComponentInScene<CollisionCp>(m_pOwner->GetScene(), "Level");
	m_pBulletManager = m_pOwner->GetComponent<BulletManagerCp>();
	m_HasInit = true;
}

void AIRecognizerCp::Update(float deltaTime)
{
	Init();
	m_State->Update(m_pOwner, deltaTime, m_pPlayers, m_pLevelCollision, m_pBulletManager);
}

void AIRecognizerCp::SetState(std::shared_ptr<RecognizerState> newState)
{
	m_State = newState;
	//m_State->SetAiCpState(this);
}

bool RecognizerState::PlayerInSight(dae::GameObject* gameObject, std::vector<std::shared_ptr<dae::GameObject>> players)
{
	for (auto p : players)
	{
		const glm::vec2 playerPos{ p->GetWorldTransform() };
		glm::vec2 pos{ gameObject->GetWorldTransform() };
		const float playerSize{ p->GetSize().x / 2 };
		const glm::vec2 tankMidPos{ playerPos.x + playerSize / 2, playerPos.y + playerSize / 2 };

		//Straight line
		if ((tankMidPos.x > pos.x && tankMidPos.x < pos.x + playerSize)
			|| (tankMidPos.y > pos.y && tankMidPos.y < pos.y + playerSize))
		{
			//std::cout << "IN STRAIGHT LINE\n";
			return true;
		}
	}
	return false;

	//Still need to check whether there is wall between enemy and player---
	//if(!m_pLevelCollision->CollisionHit(m_pOwner, playerPos))
}

void WanderState::Update(dae::GameObject* gameObject, float ,
                         std::vector<std::shared_ptr<dae::GameObject>> players, CollisionCp* levelCollision, BulletManagerCp* )
{
	gameObject->GetComponent<MoveCp>()->Move(m_Direction);

	if(levelCollision->CollisionHit(gameObject, m_Direction))
	{
		SwapDirection();
	}

	if(PlayerInSight(gameObject, players))
	{
		const glm::vec2 attackDir = m_Direction *= 300;
		m_AICp->SetState(std::make_shared<AttackState>(m_AICp, attackDir));
	}
}

void WanderState::SwapDirection()
{
	//will (maybe) do random/better direction choosing later

	if(m_Direction.x > 0.f)
	{
		m_Direction.x = 0;
		m_Direction.y = 1;
	}
	else if (m_Direction.y > 0.f)
	{
		m_Direction.x = -1;
		m_Direction.y = 0;
	}
	else if (m_Direction.x < 0.f)
	{
		m_Direction.x = 0;
		m_Direction.y = -1;
	}
	else if (m_Direction.y < 0.f)
	{
		m_Direction.x = 1;
		m_Direction.y = 0;
	}
}

void AttackState::Update(dae::GameObject* gameObject, float deltaTime,
                         std::vector<std::shared_ptr<dae::GameObject>> players, CollisionCp* , BulletManagerCp* bulletManager)
{
	//is not correct behaviour, just quick code for state pattern

	if (!m_HasShot)
	{
		bulletManager->Shoot(m_ShootDirection, false);
		m_HasShot = true;
	}
	UpdateShootTimer(deltaTime);

	if (!PlayerInSight(gameObject, players))
	{
		m_AICp->SetState(std::make_shared<WanderState>(m_AICp));
	}
}

void AttackState::UpdateShootTimer(float deltaTime)
{
	if (!m_HasShot) return;

	m_ShootTimer += deltaTime;

	if (m_ShootTimer >= m_ShootTime)
	{
		m_ShootTimer = 0;
		m_HasShot = false;
	}
}


