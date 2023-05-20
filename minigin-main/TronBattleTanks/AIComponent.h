#pragma once
#include <memory>
#include <vector>
#include <glm/vec2.hpp>

#include "BaseComponent.h"


class CollisionCp;
class BulletManagerCp;

class AIComponent final : public dae::ComponentBase
{
public:
	AIComponent(dae::GameObject* owner);
	virtual ~AIComponent() = default;

	AIComponent(const AIComponent& other) = delete;
	AIComponent(AIComponent&& other) = delete;
	AIComponent& operator=(const AIComponent& other) = delete;
	AIComponent& operator=(AIComponent&& other) = delete;

	void Update(float deltaTime) override;

private:

	bool m_HasInit{};
	bool m_HasShot{};
	float m_ShootTimer{};
	float m_ShootTime{};
	std::vector<std::shared_ptr<dae::GameObject>> m_pPlayers;
	CollisionCp* m_pLevelCollision;
	BulletManagerCp* m_pBulletManager;

	void Init();
	void FindPlayer();
	void FindLevel();
	void UpdateShootTimer(float deltaTime);
	bool PlayerInSight(glm::vec2& bulletDir);
};

