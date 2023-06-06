#include "BulletManagerCp.h"

#include <glm/vec2.hpp>

#include "BulletPrefab.h"
#include "EngineEvents.h"
#include "EventQueue.h"
#include "GameObject.h"
#include "Scene.h"
#include "TextureComponent.h"

BulletManagerCp::BulletManagerCp(dae::GameObject* owner):
ComponentBase(owner)
{}

void BulletManagerCp::Update(float deltaTime)
{
	if (!m_HasShot) return;

	m_Timer += deltaTime;
	if (m_Timer > 1)
	{
		m_Timer = 0;
		m_HasShot = false;
	}
}


void BulletManagerCp::Shoot( const glm::vec2& vel)
{
	if (m_HasShot) return;

	auto& ss = Servicelocator::GetSoundSystem();
	ss.Play(0, 100);


	auto pBullet = CreateBullet(*m_pOwner->GetScene(), m_pOwner, vel);
	pBullet->SetTag(m_pOwner->GetTag());

	const glm::vec2 middlePos = { m_pOwner->GetWorldTransform().x + m_pOwner->GetSize().x / 2 - pBullet->GetSize().x / 2,
		m_pOwner->GetWorldTransform().y + m_pOwner->GetSize().y / 2 - pBullet->GetSize().y / 2 };

	pBullet->SetRelativePos(middlePos);

	m_HasShot = true;
}

