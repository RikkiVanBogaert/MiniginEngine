#pragma once
#include <SDL_pixels.h>

#include "BulletManagerCp.h"
#include "CollisionCp.h"
#include "GameObject.h"
#include "SpawnPositionCp.h"
#include "TextureComponent.h"
#include "ResourceManager.h"
#include "TeleportPrefab.h"
#include "TextComponent.h"

using namespace dae;

static std::shared_ptr<GameObject> CreateLevel(Scene& scene, const std::string& levelPath)
{
	auto pLevelObject = std::make_shared<GameObject>();
	scene.Add(pLevelObject);
	pLevelObject->SetTag("Level");

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 13);
	
	const auto startObj = std::make_shared<GameObject>();
	const auto startText = std::make_shared<TextComponent>(startObj.get(), "Skip Level (N)", font, SDL_Color{ 255, 255, 255 });
	startObj->SetRelativePos({ 5, 400 });
	startObj->AddComponent(startText);
	pLevelObject->AddChild(startObj);

	auto collisionCp = std::make_shared<CollisionCp>(pLevelObject.get());
	pLevelObject->AddComponent(collisionCp);

	auto playerSpawnPosCp = std::make_shared<PlayerSpawnPosCp>(pLevelObject.get());
	pLevelObject->AddComponent(playerSpawnPosCp);

	auto blueEnemySpawnPosCp = std::make_shared<BlueEnemySpawnPosCp>(pLevelObject.get());
	pLevelObject->AddComponent(blueEnemySpawnPosCp);

	auto recognizerSpawnPosCp = std::make_shared<RecognizerSpawnPosCp>(pLevelObject.get());
	pLevelObject->AddComponent(recognizerSpawnPosCp);

	//Create Map
	constexpr int columns = 58;
	auto map = ResourceManager::GetInstance().ParseCsv(levelPath);
	constexpr float size{ 8 };
	constexpr glm::vec2 startPos{ 100,20 };
	glm::vec2 pos{ startPos };
	int amountPlayerSpawns{};
	int amountBlueEnemySpawns{};
	int amountRecognizerSpawns{};
	for (size_t i{}; i < map.size(); ++i)
	{
		auto pBlock = std::make_shared<GameObject>();
		auto pTexture = std::make_shared<TextureComponent>(pBlock.get());
		pLevelObject->AddChild(pBlock);
		pBlock->SetRelativePos({ pos.x, pos.y });
		pBlock->SetSize({ size, size });
		pBlock->AddComponent(pTexture);
		pTexture->SetTexture("Resources/Level/path.png");
		pBlock->SetTag("Path");

		const glm::vec2 offset{ pBlock->GetSize() };

		switch (map[i])
		{
		case 0:
			pTexture->SetTexture("Resources/Level/wall.png");
			collisionCp->AddCollider(pBlock.get());
			pBlock->SetTag("Wall");
			break;
		case 1:
			pTexture->SetTexture("Resources/Level/void.png");
			pBlock->SetTag("Teleport");
			break;
		case 3:
			CreateTeleport(scene)->SetRelativePos(pos);
			break;
		case 4:
			if (amountBlueEnemySpawns % 4 == 0)
				blueEnemySpawnPosCp->AddPos(pos);

			++amountBlueEnemySpawns;
			break;
		case 5:
			if (amountRecognizerSpawns % 4 == 0)
				recognizerSpawnPosCp->AddPos(pos);

			++amountRecognizerSpawns;
			break;
		case 6:
			if(amountPlayerSpawns % 4 == 0)
				playerSpawnPosCp->AddPos(pos);

			++amountPlayerSpawns;
			break;
		default:
			break;
		}

		pos.x += size;

		if ((i + 1) % columns == 0)
		{
			pos.x = startPos.x;
			pos.y += size;
		}
	}

	return pLevelObject;
}

