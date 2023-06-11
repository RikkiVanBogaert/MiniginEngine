#pragma once
#include <memory>
#include <vector>
#include <glm/vec2.hpp>


#include "BaseComponent.h"

class AttackState;
class WanderState;
class BulletManagerCp;
class CollisionCp;
class RecognizerState;

namespace dae
{
	class GameObject;
}

class AIRecognizerCp final : public dae::ComponentBase
{
public:
	AIRecognizerCp(dae::GameObject* owner);
	virtual ~AIRecognizerCp() override = default;

	AIRecognizerCp(const AIRecognizerCp& other) = delete;
	AIRecognizerCp(AIRecognizerCp&& other) = delete;
	AIRecognizerCp& operator=(const AIRecognizerCp& other) = delete;
	AIRecognizerCp& operator=(AIRecognizerCp&& other) = delete;

	void Update(float deltaTime) override;
	void SetState(const std::shared_ptr<RecognizerState>& newState);

protected:
	void Init();

private:
	std::shared_ptr<RecognizerState> m_State;

	bool m_HasInit{};

	std::vector<std::shared_ptr<dae::GameObject>> m_pPlayers;
	CollisionCp* m_pLevelCollision{};
	BulletManagerCp* m_pBulletManager{};

};

class RecognizerState
{
public:
	RecognizerState(AIRecognizerCp* cp = nullptr):
	m_pAICp(cp){}
	virtual ~RecognizerState() = default;

	RecognizerState(const RecognizerState& other) = delete;
	RecognizerState(RecognizerState&& other) = delete;
	RecognizerState& operator=(const RecognizerState& other) = delete;
	RecognizerState& operator=(RecognizerState&& other) = delete;

	virtual void Update(dae::GameObject* gameObject, float deltaTime, 
		std::vector<std::shared_ptr<dae::GameObject>> players, CollisionCp* levelCollision, BulletManagerCp* bulletManager) = 0;

	static std::shared_ptr<WanderState> m_pWanderState;
	static std::shared_ptr<AttackState> m_pAttackState;

protected:
	bool PlayerInSight(dae::GameObject* gameObject, const std::vector<std::shared_ptr<dae::GameObject>>& players);
	AIRecognizerCp* GetAICp() const { return m_pAICp; }
	glm::vec2 GetToPlayer() const { return m_ToPlayer; }

private:
	AIRecognizerCp* m_pAICp{};
	glm::vec2 m_ToPlayer{};
};

class WanderState final : public RecognizerState
{
public:
	WanderState(AIRecognizerCp* cp = nullptr) :
	RecognizerState(cp) {}
	void Update(dae::GameObject* gameObject, float deltaTime, 
		std::vector<std::shared_ptr<dae::GameObject>> players, CollisionCp* levelCollision, BulletManagerCp* bulletManager) override;

private:
	glm::vec2 m_Direction{};
};

class AttackState final : public RecognizerState
{
public:
	AttackState(AIRecognizerCp* cp = nullptr, const glm::vec2& shootDir = {0,0}):
	RecognizerState(cp), m_ShootDirection(shootDir) {}

	void Update(dae::GameObject* gameObject, float deltaTime, 
		std::vector<std::shared_ptr<dae::GameObject>> players, CollisionCp* levelCollision, BulletManagerCp* bulletManager) override;

private:
	const glm::vec2 m_ShootDirection{};
	bool m_HasShot{};
	float m_ShootTimer{};
	const float m_ShootDelay{3};

	void UpdateShootTimer(float deltaTime);
};