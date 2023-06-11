#pragma once
#include <memory>
#include <vector>
#include <glm/vec2.hpp>

#include "BaseComponent.h"


class AttackState;
class WanderState;
class RecognizerState;
class CollisionCp;
class BulletManagerCp;

class AIComponent final : public dae::ComponentBase
{
public:
	AIComponent(dae::GameObject* owner);
	virtual ~AIComponent() override = default;

	AIComponent(const AIComponent& other) = delete;
	AIComponent(AIComponent&& other) = delete;
	AIComponent& operator=(const AIComponent& other) = delete;
	AIComponent& operator=(AIComponent&& other) = delete;

	void Update(float deltaTime) override;

private:

	const float m_ShootDelay{};
	float m_ShootTimer{};
	bool m_HasShot{};
	bool m_HasInit{};
	std::vector<std::shared_ptr<dae::GameObject>> m_pPlayers;
	dae::GameObject* m_pClosestPlayer{};
	CollisionCp* m_pLevelCollision{};
	BulletManagerCp* m_pBulletManager{};

	void Init();
	void UpdateShootTimer(float deltaTime);
	bool PlayerInSight(glm::vec2& bulletDir) const;
	void GoToPlayer(float) const;
	void GetClosestPlayer();
};

