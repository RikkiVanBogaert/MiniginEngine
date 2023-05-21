#pragma once
#include "BaseComponent.h"

class LevelInfoCp final : public dae::ComponentBase
{
public:
	LevelInfoCp(dae::GameObject* owner);
	void Update(float deltaTime) override;

private:
	void CheckIfLevelComplete();
};

