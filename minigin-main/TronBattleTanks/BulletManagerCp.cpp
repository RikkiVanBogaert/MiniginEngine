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


void BulletManagerCp::Shoot( const glm::vec2& vel) const
{
	auto& ss = servicelocator::get_sound_system();
	ss.play(0, 100);


	auto pBullet = CreateBullet(*m_pOwner->GetScene(), m_pOwner, vel);
	pBullet->SetTag(m_pOwner->GetTag());

	const glm::vec2 middlePos = { m_pOwner->GetWorldTransform().x + m_pOwner->GetSize().x / 2 - pBullet->GetSize().x / 2,
		m_pOwner->GetWorldTransform().y + m_pOwner->GetSize().y / 2 - pBullet->GetSize().y / 2 };

	pBullet->SetRelativePos(middlePos);

}

