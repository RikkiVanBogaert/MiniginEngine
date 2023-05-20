//#pragma once
//#include "BaseComponent.h"
//
//class Level;
//class Tank;
//
//class AIComponent final : public dae::ComponentBase
//{
//public:
//	AIComponent(dae::GameObject* owner);
//	virtual ~AIComponent() = default;
//
//	AIComponent(const AIComponent& other) = delete;
//	AIComponent(AIComponent&& other) = delete;
//	AIComponent& operator=(const AIComponent& other) = delete;
//	AIComponent& operator=(AIComponent&& other) = delete;
//
//	void Update(float deltaTime) override;
//
//private:
//
//	bool m_HasInit{};
//	bool m_HasShot{};
//	float m_ShootTimer{};
//	float m_ShootTime{};
//
//	Tank* m_pAiOwner;
//	Tank* m_pPlayer = nullptr;
//	Level* m_pLevel = nullptr;
//
//	void Init();
//	void FindPlayer();
//	void FindLevel();
//	void ResetShootTimer(float deltaTime);
//};
//
