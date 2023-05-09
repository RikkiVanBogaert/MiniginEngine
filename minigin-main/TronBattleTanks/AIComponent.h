#pragma once
#include "BaseComponent.h"

class Level;
class Tank;

class AIComponent final : public dae::ComponentBase
{
public:
	AIComponent(dae::GameObject* owner);


	void Update(float deltaTime) override;

private:

	void FindPlayer();
	void FindLevel();
	Tank* m_pAiOwner;
	Tank* m_pPlayer;
	Level* m_pLevel;
};

