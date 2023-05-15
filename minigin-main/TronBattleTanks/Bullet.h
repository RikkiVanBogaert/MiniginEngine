#pragma once
#include "GameObject.h"
#include "Transform.h"

class Tank;

class Bullet final : public dae::GameObject
{
public:
	Bullet(Tank* shooter, glm::vec2 velocity);
	virtual ~Bullet() = default;

	Bullet(const Bullet& other) = delete;
	Bullet(Bullet&& other) = delete;
	Bullet& operator=(const Bullet& other) = delete;
	Bullet& operator=(Bullet&& other) = delete;

	virtual void Update(float deltaTime) override;
	void SetVelocity(glm::vec2 newVel);
	glm::vec2 GetVelocity() const { return m_Velocity; }
	Tank* GetShooter() { return m_pShooter; }

private:
	glm::vec2 m_Velocity{};
	int m_NrBounces{};
	Tank* m_pShooter;
};
