#pragma once
#include "BaseComponent.h"

class LevelInfoCp final : public dae::ComponentBase
{
public:
	LevelInfoCp(dae::GameObject* owner);
	virtual ~LevelInfoCp() override;

	LevelInfoCp(const LevelInfoCp& other) = delete;
	LevelInfoCp(LevelInfoCp&& other) = delete;
	LevelInfoCp& operator=(const LevelInfoCp& other) = delete;
	LevelInfoCp& operator=(LevelInfoCp&& other) = delete;

	void Update(float deltaTime) override;

private:
	void CheckIfLevelComplete() const;
};

