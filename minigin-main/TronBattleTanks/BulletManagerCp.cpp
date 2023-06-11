#include "BulletManagerCp.h"


#include "AudioService.h"
#include "BulletPrefab.h"
#include "GameObject.h"
#include "Sounds.h"

#include <glm/vec2.hpp>
#include <glm/glm.hpp>

BulletManagerCp::BulletManagerCp(dae::GameObject* owner, float bulletSpeed):
ComponentBase(owner),
m_BulletSpeed(bulletSpeed)
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


void BulletManagerCp::Shoot( const glm::vec2& vel, bool playerBullet)
{
	if (m_HasShot) return;

	auto& ss = dae::ServiceLocator::GetSoundSystem();
	ss.Play(Sounds::Shoot, 100, 0, Sounds::Shoot);

	const auto bulletVelocity = glm::normalize(vel) * m_BulletSpeed;
	const auto pBullet = CreateBullet(*m_pOwner->GetScene(), m_pOwner, bulletVelocity, playerBullet);
	pBullet->SetTag(m_pOwner->GetTag());

	const glm::vec2 middlePos = { m_pOwner->GetWorldTransform().x + m_pOwner->GetSize().x / 2 - pBullet->GetSize().x / 2,
		m_pOwner->GetWorldTransform().y + m_pOwner->GetSize().y / 2 - pBullet->GetSize().y / 2 };

	pBullet->SetRelativePos(middlePos);

	m_HasShot = true;
}

