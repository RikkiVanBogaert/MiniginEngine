#pragma once
#include "GameObject.h"
#include "Transform.h"

class Bullet final : public dae::GameObject
{
public:
	Bullet(glm::vec2 velocity);
	
	virtual void Update(float deltaTime) override;
	void SetVelocity(glm::vec2 newVel);
	glm::vec2 GetVelocity() const { return m_Velocity; }

private:
	glm::vec2 m_Velocity{};
	int m_NrBounces{};

};
