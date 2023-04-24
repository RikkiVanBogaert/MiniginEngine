#pragma once
#include "GameObject.h"
#include "Transform.h"

#include <memory>


class Bullet final : public GameObject
{
public:
	Bullet(glm::vec3 velocity);
	virtual ~Bullet() {};

	virtual void Update(float deltaTime) override;

private:
	glm::vec3 m_Velocity{};

};