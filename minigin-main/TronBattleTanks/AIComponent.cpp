//#include "AIComponent.h"
//
//#include "GameObject.h"
//#include "Scene.h"
//#include "Tank.h"
//#include "PlayerManager.h"
//
//AIComponent::AIComponent(dae::GameObject* owner):
//	ComponentBase(owner),
//	m_ShootTime{3}
//{
//	m_pAiOwner = dynamic_cast<EnemyTank*>(owner);
//}
//
//void AIComponent::Update(float deltaTime)
//{
//	Init();
//
//	if (m_HasShot)
//	{
//		ResetShootTimer(deltaTime);
//		return;
//	}
//
//	if (!m_pPlayer || m_pPlayer->NeedsDeleting()) return;
//
//	const auto playerPos = m_pPlayer->GetRelativeTransform();
//	const auto playerDir = playerPos - m_pOwner->GetRelativeTransform();
//	const float dirLength = sqrtf(playerDir.x * playerDir.x + playerDir.y * playerDir.y);
//	const glm::vec2 playerDirNormalized = { playerDir.x / dirLength, playerDir.y / dirLength };
//	constexpr float bulletSpeed{ 250 };
//	const glm::vec2 bulletDir{ playerDirNormalized.x * bulletSpeed, playerDirNormalized.y * bulletSpeed };
//
//	//if(!m_pLevel->HitWall(m_pAiOwner->GetRelativeTransform(), playerPos))
//	//{
//	//	//m_pAiOwner->ShootBullet(bulletDir); //causes error on debug when second bullet of a tank gets shot
//	//	m_HasShot = true;
//	//}
//
//	////else, find a way around it.
//}
//
//void AIComponent::Init()
//{
//	if (m_HasInit) return;
//	FindPlayer();
//	FindLevel();
//	m_HasInit = true;
//}
//
//void AIComponent::FindPlayer()
//{
//	//m_pPlayer = dynamic_cast<PlayerTank*>(PlayerManager::GetInstance().GetPlayers()[0].get());
//}
//
////Make helper function which finds an object of a certain type in the scene
//
//void AIComponent::FindLevel()
//{
//	/*for (auto& o : m_pOwner->GetScene()->GetGameObjects())
//	{
//		if (!dynamic_cast<Level*>(o.get())) continue;
//
//		m_pLevel = dynamic_cast<Level*>(o.get());
//	}*/
//}
//
//void AIComponent::ResetShootTimer(float deltaTime)
//{
//	m_ShootTimer += deltaTime;
//
//	if(m_ShootTimer >= m_ShootTime)
//	{
//		m_ShootTimer = 0;
//		m_HasShot = false;
//	}
//}
