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


void BulletManagerCp::Shoot(const glm::vec2& vel)
{
	auto& event_queue = EventQueue<Event, float>::GetInstance();
	event_queue.schedule(SoundEvent(1, 0), 0);


	auto pBullet = CreateBullet(*m_pOwner->GetScene(), vel);

	const glm::vec2 middlePos = { m_pOwner->GetWorldTransform().x + m_pOwner->GetSize().x / 2 - pBullet->GetSize().x / 2,
		m_pOwner->GetWorldTransform().y + m_pOwner->GetSize().y / 2 - pBullet->GetSize().y / 2 };

	pBullet->SetRelativePos(middlePos);

}

