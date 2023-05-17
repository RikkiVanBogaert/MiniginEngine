#pragma once
#include <vector>

#include "BaseComponent.h"

class BulletManagerCp final : public dae::ComponentBase
{
public:
	BulletManagerCp(dae::GameObject* owner);

	void AddBullet(dae::GameObject* bullet) { m_pBullets.emplace_back(bullet); }
private:
	std::vector<dae::GameObject*> m_pBullets;
};

