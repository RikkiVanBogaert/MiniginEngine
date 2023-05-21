#pragma once
#include "BulletCollisionCp.h"
#include "BulletManagerCp.h"
#include "Scene.h"
#include "TextureComponent.h"
#include "GameObject.h"
#include "CollisionCp.h"
#include "AIComponent.h"
#include "CounterCp.h"
#include "MoveCp.h"

static dae::GameObject* CreateBlueEnemy(dae::Scene& scene)
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

	auto healthCp = std::make_shared<HealthCp>(pTank.get(), 3);
	pTank->AddComponent(healthCp);

	auto bulletCollisionCp = std::make_shared<BulletCollisionCp>(pTank.get());
	pTank->AddComponent(bulletCollisionCp);

	auto bulletManagerCP = std::make_shared<BulletManagerCp>(pTank.get());
	pTank->AddComponent(bulletManagerCP);

	auto pAICp = std::make_shared<AIComponent>(pTank.get());
	pTank->AddComponent(pAICp);

	auto pMoveCp = std::make_shared<MoveCp>(pTank.get());
	pTank->AddComponent(pMoveCp);

	return pTank.get();
}

static void CreateBlueEnemies(dae::Scene& scene, const std::vector<glm::vec2>& positions)
{
	constexpr glm::vec2 offset{ -8,-8 };
	for(int i{}; i < positions.size(); ++i)
	{
		auto enemy = CreateBlueEnemy(scene);
		enemy->SetRelativePos(positions[i] + offset);
	}
}


static dae::GameObject* CreateRecognizer(dae::Scene& scene)
{
	auto pTank = std::make_shared<dae::GameObject>();
	scene.Add(pTank);

	//Texture
	auto tankTxt = std::make_shared<dae::TextureComponent>(pTank.get());
	tankTxt->SetTexture("Resources/Sprites/Recognizer.png");
	pTank->AddComponent(tankTxt);

	auto collisionCp = std::make_shared<CollisionCp>(pTank.get());
	pTank->AddComponent(collisionCp);
	collisionCp->AddCollider(pTank.get());

	auto healthCp = std::make_shared<HealthCp>(pTank.get(), 3);
	pTank->AddComponent(healthCp);

	auto bulletCollisionCp = std::make_shared<BulletCollisionCp>(pTank.get(), 250);
	pTank->AddComponent(bulletCollisionCp);

	auto bulletManagerCP = std::make_shared<BulletManagerCp>(pTank.get());
	pTank->AddComponent(bulletManagerCP);

	auto pAICp = std::make_shared<AIComponent>(pTank.get(), 60.f);
	pTank->AddComponent(pAICp);

	auto pMoveCp = std::make_shared<MoveCp>(pTank.get());
	pTank->AddComponent(pMoveCp);

	return pTank.get();
}

static void CreateRecognizers(dae::Scene& scene, const std::vector<glm::vec2>& positions)
{
	constexpr glm::vec2 offset{ -8,-8 };
	for (int i{}; i < positions.size(); ++i)
	{
		auto enemy = CreateRecognizer(scene);
		enemy->SetRelativePos(positions[i] + offset);
	}
}