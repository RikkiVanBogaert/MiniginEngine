#pragma once
#include <SDL_pixels.h>

#include "CollisionCp.h"
#include "GameObject.h"
#include "GridCp.h"
#include "LevelInfoCp.h"
#include "SpawnPositionCp.h"
#include "TextureComponent.h"
#include "ResourceManager.h"
#include "TeleportPrefab.h"
#include "TextComponent.h"

namespace dae
{

	static std::shared_ptr<GameObject> CreateLevel(Scene& scene, const std::string& levelPath)
	{
		auto pLevelObject = std::make_shared<GameObject>();
		scene.Add(pLevelObject);
		pLevelObject->SetTag("Level");

		auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 13);

		const auto startObj = std::make_shared<GameObject>();
		const auto startText = std::make_shared<TextComponent>(startObj.get(), "Skip Level (N)", font, SDL_Color{ 255, 255, 255, 255 });
		startObj->SetRelativePos({ 5, 400 });
		startObj->AddComponent(startText);
		pLevelObject->AddChild(startObj);

		const auto infoCp = std::make_shared<LevelInfoCp>(pLevelObject.get());
		pLevelObject->AddComponent(infoCp);

		const auto collisionCp = std::make_shared<CollisionCp>(pLevelObject.get());
		pLevelObject->AddComponent(collisionCp);

		const auto playerSpawnPosCp = std::make_shared<PlayerSpawnPosCp>(pLevelObject.get());
		pLevelObject->AddComponent(playerSpawnPosCp);

		const auto blueEnemySpawnPosCp = std::make_shared<BlueEnemySpawnPosCp>(pLevelObject.get());
		pLevelObject->AddComponent(blueEnemySpawnPosCp);

		const auto recognizerSpawnPosCp = std::make_shared<RecognizerSpawnPosCp>(pLevelObject.get());
		pLevelObject->AddComponent(recognizerSpawnPosCp);

		const auto gridCp = std::make_shared<GridCp>(pLevelObject.get());
		pLevelObject->AddComponent(gridCp);

		//Create Map
		constexpr int amountCols = 58;
		int curRow{};
		int curCol{};
		const auto map = ResourceManager::GetInstance().ParseCsv(levelPath);
		constexpr float size{ 8 };
		constexpr glm::vec2 startPos{ 100,20 };
		glm::vec2 pos{ startPos };
		int amountPlayerSpawns{};
		int amountBlueEnemySpawns{};
		int amountRecognizerSpawns{};

		std::vector<glm::vec2> teleports;
		std::vector<int> teleportPlaces;

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
				break;
			case 2:
				//path
				if(curRow % 2 == 1 && curCol % 2 == 1 && 
					curCol < amountCols - 6)
				{
					teleportPlaces.emplace_back(int(i));
				}
				break;
			case 3:
				pTexture->SetTexture("Resources/Level/path.png");
				pBlock->SetTag("Teleport");
				teleports.emplace_back(pos);
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
				if (amountPlayerSpawns % 4 == 0)
				{
					auto spawnPos = pos;
					spawnPos -= offset;
					playerSpawnPosCp->AddPos(spawnPos);
				}

				++amountPlayerSpawns;
				break;
			default:
				break;
			}
			gridCp->AddCell({ pBlock->GetTag(), pos });

			pos.x += size;
			++curCol;
			if(gridCp->m_GridRows == 0)
				++gridCp->m_GridCols;

			if ((i + 1) % amountCols == 0)
			{
				pos.x = startPos.x;
				pos.y += size;
				++curRow;
				curCol = 0;
				++gridCp->m_GridRows;
			}
		}

		for(auto t : teleports)
		{
			CreateTeleport(scene, teleportPlaces)->SetRelativePos(t);
		}

		return pLevelObject;
	}
}