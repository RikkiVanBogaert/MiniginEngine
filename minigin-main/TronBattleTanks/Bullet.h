#pragma once
#include "GameObject.h"
#include "Transform.h"

#include <memory>

class Bullet final : public dae::GameObject
{
public:
	Bullet(glm::vec3 velocity);
	virtual ~Bullet() {};

	virtual void Update(float deltaTime) override;
	void SetVelocity(glm::vec3 newVel);
	glm::vec3 GetVelocity() const { return m_Velocity; }

private:
	glm::vec3 m_Velocity{};
	int m_NrBounces{};

};
