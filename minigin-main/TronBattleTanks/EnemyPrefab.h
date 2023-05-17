#pragma once
#include "Scene.h"
#include "TextureComponent.h"
#include "GameObject.h"

static dae::GameObject* CreateEnemy(dae::Scene& scene)
{
	auto pTank = std::make_shared<dae::GameObject>();
	scene.Add(pTank);
	
	//Texture
	auto tankTxt = std::make_shared<dae::TextureComponent>(pTank.get());
	tankTxt->SetTexture("Resources/Sprites/BlueTank.png");
	pTank->AddComponent(tankTxt);

	return pTank.get();
}

static void CreateEnemies(dae::Scene& scene, const std::vector<glm::vec2>& positions)
{
	constexpr glm::vec2 offset{ -8,-8 };
	for(int i{}; i < positions.size(); ++i)
	{
		auto enemy = CreateEnemy(scene);
		enemy->SetRelativePos(positions[i] + offset);
	}
}
