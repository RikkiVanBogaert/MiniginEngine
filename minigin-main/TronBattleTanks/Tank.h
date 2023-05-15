#pragma once
#include "GameObject.h"
#include "CounterCp.h"

#include <memory>

class AIComponent;


class Tank : public dae::GameObject
{
public:
	enum Type
	{
		Red,
		Blue
	};

	Tank(Type type);

	virtual ~Tank() = default;
	Tank(const Tank& other) = delete;
	Tank(Tank&& other) = delete;
	Tank& operator=(const Tank& other) = delete;
	Tank& operator=(Tank&& other) = delete;

	virtual void Update(float deltaTime) override;
	void ShootBullet(const glm::vec2& direction);

protected:
	std::shared_ptr<GameObject> m_pGun;
	std::shared_ptr<dae::HealthCp> m_pHealth;


private:
	Type m_Type;

	void InitType();
	void CheckOverlap();
	virtual void GetHit() = 0;

};

class PlayerTank final : public Tank
{
public:
	PlayerTank(Type type);
	virtual ~PlayerTank() override = default;

private:

	virtual void GetHit() override;

};

class EnemyTank final : public Tank
{
public:
	EnemyTank();
	virtual ~EnemyTank() override = default;

private:
	std::shared_ptr<AIComponent> m_pAICp;

	virtual void GetHit() override;

};

