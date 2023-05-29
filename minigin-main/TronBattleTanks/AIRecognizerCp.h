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
	AIRecognizerCp(dae::GameObject* owner, float speed = 30);
	virtual ~AIRecognizerCp() = default;

	AIRecognizerCp(const AIRecognizerCp& other) = delete;
	AIRecognizerCp(AIRecognizerCp&& other) = delete;
	AIRecognizerCp& operator=(const AIRecognizerCp& other) = delete;
	AIRecognizerCp& operator=(AIRecognizerCp&& other) = delete;

	void Update(float deltaTime) override;
	void SetState(std::shared_ptr<RecognizerState> newState);

protected:
	void Init();

private:
	std::shared_ptr<RecognizerState> m_State;

	const float m_Speed;
	bool m_HasInit{};

	std::vector<std::shared_ptr<dae::GameObject>> m_pPlayers;
	dae::GameObject* m_pClosestPlayer{};
	CollisionCp* m_pLevelCollision{};
	BulletManagerCp* m_pBulletManager{};

};

class RecognizerState
{
public:
	RecognizerState(AIRecognizerCp* cp = nullptr): m_AICp(cp){}
	virtual ~RecognizerState() = default;
	virtual void Update(dae::GameObject* gameObject, float deltaTime, 
		std::vector<std::shared_ptr<dae::GameObject>> players, CollisionCp* levelCollision, BulletManagerCp* bulletManager) = 0; //pass everything by argument

	static std::shared_ptr<WanderState> m_WanderState;
	static std::shared_ptr<AttackState> m_AttackState;

	//void SetAiCpState(AIRecognizerCp* cp) { m_AICp = cp; }

protected:
	AIRecognizerCp* m_AICp;

	bool PlayerInSight(dae::GameObject* gameObject, std::vector<std::shared_ptr<dae::GameObject>> players);

};

class WanderState final : public RecognizerState
{
public:
	WanderState(AIRecognizerCp* cp = nullptr) : RecognizerState(cp) {}
	void Update(dae::GameObject* gameObject, float deltaTime, 
		std::vector<std::shared_ptr<dae::GameObject>> players, CollisionCp* levelCollision, BulletManagerCp* bulletManager) override;

private:
	glm::vec2 m_Direction{1,0};

	void SwapDirection();
};

class AttackState final : public RecognizerState
{
public:
	AttackState(AIRecognizerCp* cp = nullptr, const glm::vec2& shootDir = {0,0}): RecognizerState(cp), m_ShootDirection(shootDir) {}

	void Update(dae::GameObject* gameObject, float deltaTime, 
		std::vector<std::shared_ptr<dae::GameObject>> players, CollisionCp* levelCollision, BulletManagerCp* bulletManager) override;

private:
	glm::vec2 m_ShootDirection;
	bool m_HasShot{};
	float m_ShootTimer{};
	const float m_ShootTime{3};

	void UpdateShootTimer(float deltaTime);
};