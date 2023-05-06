#pragma once
#include "GameObject.h"
#include "TextComponent.h"
#include <vector>
#include <memory>

class Menu final : public dae::GameObject
{
public:
	Menu(dae::Scene* scene);
	virtual void Update(float deltaTime) override;

private:
	//GameMode m_GameMode{ GameMode::SinglePlayer };
	std::shared_ptr<dae::GameObject> m_pGameModeObject;
	std::shared_ptr<dae::TextComponent> m_pGameModeText;

	void InitMenu();
	void SetGameModeText();
};

