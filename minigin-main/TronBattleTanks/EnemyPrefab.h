#pragma once
#include "BulletCollisionCp.h"
#include "Scene.h"
#include "TextureComponent.h"
#include "GameObject.h"
#include "CollisionCp.h"
#include "CounterCp.h"

static dae::GameObject* CreateEnemy(dae::Scene& scene)
{
	auto pTank = std::make_shared<dae::GameObject>();
	scene.Add(pTank);
	
	//Texture
	auto tankTxt = std::make_shared<dae::TextureComponent>(pTank.get());
	tankTxt->SetTexture("Resources/Sprites/BlueTank.png");
	pTank->AddComponent(tankTxt);

	auto collisionCp = std::make_shared<CollisionCp>(pTank.get());
	pTank->AddComponent(collisionCp);
	collisionCp->AddCollider(pTank.get());

	auto healthCp = std::make_shared<dae::HealthCp>(pTank.get(), 3);
	pTank->AddComponent(healthCp);

	auto bulletCollisionCp = std::make_shared<BulletCollisionCp>(pTank.get());
	pTank->AddComponent(bulletCollisionCp);

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
