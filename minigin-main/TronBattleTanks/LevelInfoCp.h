#pragma once
#include "BaseComponent.h"

class LevelInfoCp final : public dae::ComponentBase
{
public:
	LevelInfoCp(dae::GameObject* owner);
	~LevelInfoCp();
	void Update(float deltaTime) override;

private:
	void CheckIfLevelComplete() const;
};

