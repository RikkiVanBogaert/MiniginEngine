#pragma once
#include "BulletManagerCp.h"
#include "CollisionCp.h"
#include "GameObject.h"
#include "SpawnPositionCp.h"
#include "TextureComponent.h"
#include "ResourceManager.h"

using namespace dae;

static std::shared_ptr<GameObject> CreateLevel(Scene& scene, const std::string& levelPath)
{
	auto pLevelObject = std::make_shared<GameObject>();
	scene.Add(pLevelObject);
	pLevelObject->SetTag("Level");

	auto collisionCp = std::make_shared<CollisionCp>(pLevelObject.get());
	pLevelObject->AddComponent(collisionCp);

	auto playerSpawnPosCp = std::make_shared<PlayerSpawnPosCp>(pLevelObject.get());
	pLevelObject->AddComponent(playerSpawnPosCp);

	auto enemySpawnPosCp = std::make_shared<EnemySpawnPosCp>(pLevelObject.get());
	pLevelObject->AddComponent(enemySpawnPosCp);

	constexpr int columns = 58;
	auto map = ResourceManager::GetInstance().ParseCsv(levelPath);
	constexpr float size{ 8 };
	constexpr glm::vec2 startPos{ 100,20 };
	glm::vec2 pos{ startPos };
	int amountPlayerSpawns{};
	int amountEnemySpawns{};
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
			break;
		case 1:
			pTexture->SetTexture("Resources/Level/void.png");
			break;
		case 3:
			pTexture->SetTexture("Resources/Level/teleport.png");
			pBlock->SetTag("Teleport");
			//m_pTeleport.push_back(pBlock.get());
			break;
		case 4:
			if (amountEnemySpawns % 4 == 0)
				enemySpawnPosCp->AddPos(pos);

			++amountEnemySpawns;
			break;
		case 6:
			if(amountPlayerSpawns % 4 == 0)
				playerSpawnPosCp->AddPos(pos);

			++amountPlayerSpawns;
			break;
		default:
			//m_pPaths.push_back(pBlock.get());
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

