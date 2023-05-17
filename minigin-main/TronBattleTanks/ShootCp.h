#pragma once
#include <vector>
#include <glm/vec2.hpp>

#include "BaseComponent.h"
#include "Bullet.h"
#include "EngineEvents.h"
#include "EventQueue.h"
#include "Sounds.h"
#include "Scene.h"

class ShootCp final : public dae::ComponentBase
{
public:
	ShootCp(dae::GameObject* owner, glm::vec2 direction) :
		ComponentBase(owner), m_Direction(direction) {}

	virtual void Update(float deltaTime) override
	{
		auto& event_queue = EventQueue<Event, float>::GetInstance();
		event_queue.schedule(SoundEvent(1, Shoot), 0);

		const auto bullet = std::make_shared<Bullet>(m_pOwner.get(), m_Direction);
		bullet->SetTag(m_pOwner->GetTag());

		const glm::vec2 middlePos = { m_pOwner->GetWorldTransform().x + m_pOwner->GetSize().x / 2 - bullet->GetSize().x / 2,
			m_pOwner->GetWorldTransform().y + m_pOwner->GetSize().y / 2 - bullet->GetSize().y / 2 };
		bullet->SetRelativePos(middlePos);

		m_pOwner->GetScene()->Add(bullet);
	}

private:
	const glm::vec2 m_Direction;
};
