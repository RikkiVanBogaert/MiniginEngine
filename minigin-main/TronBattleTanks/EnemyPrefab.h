#pragma once
#include "BulletCollisionCp.h"
#include "BulletManagerCp.h"
#include "Scene.h"
#include "TextureComponent.h"
#include "GameObject.h"
#include "CollisionCp.h"
#include "AIComponent.h"
#include "AIRecognizerCp.h"
#include "EnemyHealthCp.h"
#include "MoveCp.h"

static dae::GameObject* CreateBlueEnemy(dae::Scene& scene)
{
	const auto pTank = std::make_shared<dae::GameObject>();
	pTank->SetTag("BlueEnemy");
	scene.Add(pTank);
	
	//Texture
	const auto tankTxt = std::make_shared<dae::TextureComponent>(pTank.get());
	tankTxt->SetTexture("Resources/Sprites/BlueTank.png");
	pTank->AddComponent(tankTxt);

	const auto collisionCp = std::make_shared<CollisionCp>(pTank.get());
	pTank->AddComponent(collisionCp);
	collisionCp->AddCollider(pTank.get());

	const auto healthCp = std::make_shared<EnemyHealthCp>(pTank.get(), 3);
	pTank->AddComponent(healthCp);

	const auto bulletCollisionCp = std::make_shared<BulletCollisionCp>(pTank.get());
	pTank->AddComponent(bulletCollisionCp);

	const auto bulletManagerCP = std::make_shared<BulletManagerCp>(pTank.get(), 160.f);
	pTank->AddComponent(bulletManagerCP);

	const auto pAICp = std::make_shared<AIComponent>(pTank.get());
	pTank->AddComponent(pAICp);

	const auto pMoveCp = std::make_shared<MoveCp>(pTank.get(), 25.f);
	pTank->AddComponent(pMoveCp);

	return pTank.get();
}

static void CreateBlueEnemies(dae::Scene& scene, const std::vector<glm::vec2>& positions)
{
	constexpr glm::vec2 offset{ -8,-8 };
	for(const auto p : positions)
	{
		const auto enemy = CreateBlueEnemy(scene);
		enemy->SetRelativePos(p + offset);
	}
}


static dae::GameObject* CreateRecognizer(dae::Scene& scene)
{
	const auto pTank = std::make_shared<dae::GameObject>();
	pTank->SetTag("Recognizer");
	scene.Add(pTank);

	//Texture
	const auto tankTxt = std::make_shared<dae::TextureComponent>(pTank.get());
	tankTxt->SetTexture("Resources/Sprites/Recognizer.png");
	pTank->AddComponent(tankTxt);

	const auto collisionCp = std::make_shared<CollisionCp>(pTank.get());
	pTank->AddComponent(collisionCp);
	collisionCp->AddCollider(pTank.get());

	const auto healthCp = std::make_shared<EnemyHealthCp>(pTank.get(), 3);
	pTank->AddComponent(healthCp);

	const auto bulletCollisionCp = std::make_shared<BulletCollisionCp>(pTank.get(), 250);
	pTank->AddComponent(bulletCollisionCp);

	const auto bulletManagerCP = std::make_shared<BulletManagerCp>(pTank.get());
	pTank->AddComponent(bulletManagerCP);

	const auto pAICp = std::make_shared<AIRecognizerCp>(pTank.get());
	pTank->AddComponent(pAICp);

	const auto pMoveCp = std::make_shared<MoveCp>(pTank.get(), 50.f);
	pTank->AddComponent(pMoveCp);

	return pTank.get();
}

static void CreateRecognizers(dae::Scene& scene, const std::vector<glm::vec2>& positions)
{
	constexpr glm::vec2 offset{ -8,-8 };
	for (const auto p : positions)
	{
		const auto enemy = CreateRecognizer(scene);
		enemy->SetRelativePos(p + offset);
	}
}