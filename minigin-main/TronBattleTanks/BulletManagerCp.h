#pragma once
#include <vector>
#include <glm/vec2.hpp>

#include "BaseComponent.h"

class BulletManagerCp final : public dae::ComponentBase
{
public:
	BulletManagerCp(dae::GameObject* owner);

	void Shoot( glm::vec2& vel) const;

private:


};

