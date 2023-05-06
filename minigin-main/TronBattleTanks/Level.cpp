#include "Level.h"
#include "ResourceManager.h"
#include "Scene.h"

//Components
#include "TextComponent.h"
#include "TextureComponent.h"
#include "FPSComponent.h"
#include "RotationCp.h"
#include "CounterCp.h"
#include "UICp.h"

#include "GameObject.h"
#include "Scene.h"
#include "InputManager.h"
#include "Observers.h"

#include "GameCommands.h"
#include "Tank.h"
#include "Bullet.h"

#include "PlayerManager.h"

using namespace dae;

Level::Level(std::vector<int> map, dae::Scene* scene)
{
	SetScene(scene);
	CreateMap(map, 58);
}

void Level::Update(float)
{
	UpdateBullets();
}


void Level::CreateMap(std::vector<int> map, int columns)
{
	//const int rows{54};
	//const int cols{ 58 };
	const float size{ 8 };
	const glm::vec2 startPos{ 100,10 };
	glm::vec2 pos{ startPos };
	for (int i{}; i < map.size(); ++i)
	{
		auto pBlock = std::make_shared<GameObject>();
		auto pTexture = std::make_shared<TextureComponent>(pBlock.get());
		AddChild(pBlock.get());
		pBlock->SetRelativePos({ pos.x, pos.y });
		pBlock->SetSize({ size, size });
		pBlock->AddComponent(pTexture);
		pTexture->SetTexture("Resources/Level/path.png");
		pBlock->SetTag("Path");

		const glm::vec2 offset{pBlock->GetSize()};
		switch (map[i])
		{
		case 0:
			pTexture->SetTexture("Resources/Level/wall.png");
			pBlock->SetTag("Wall");
			m_pWalls.push_back(pBlock.get());
			break;
		case 1:
			pTexture->SetTexture("Resources/Level/void.png");
			break;
		case 3:
			pTexture->SetTexture("Resources/Level/teleport.png");
			pBlock->SetTag("Teleport");
			m_pTeleport.push_back(pBlock.get());
			break;
		case 4:
			m_SpawnPosBlueTanks.push_back({ pos.x - offset.x, pos.y - offset.y });
			break;
		case 6:
			if(m_SpawnPos.x == 0)
				m_SpawnPos = { pos.x - offset.x, pos.y - offset.y };
			break;
		default:
			m_pPaths.push_back(pBlock.get());
			break;
		}


		m_pLevelObjects.push_back(std::move(pBlock));

		pos.x += size;

		if ((i + 1) % columns == 0)
		{
			pos.x = startPos.x;
			pos.y += size;
		}
	}
}

glm::vec2 Level::GetRandomSpawnPos() const
{
	const int rndIndex = rand() % (m_pPaths.size() + 1);
	const auto spawnPos = m_pPaths[rndIndex]->GetWorldTransform();

	return spawnPos;
}

void Level::LoadEnemies()
{
	for (int i{}; i < m_SpawnPosBlueTanks.size(); i += 4)
	{
		auto blueTank = std::make_shared<BlueTank>();
		blueTank->SetRelativePos(m_SpawnPosBlueTanks[i]);
		GetScene()->Add(blueTank);
	}
}

void Level::OnLevelLoad()
{	
	auto player = PlayerManager::getInstance().GetPlayers()[0];
	player->SetRelativePos(m_SpawnPos);

	player->GetScene()->Remove(player);
	GetScene()->Add(player);

	LoadEnemies();
}

void Level::OnLevelDestroy()
{
	for (auto& object : GetScene()->GetGameObjects())
	{
		if (dynamic_cast<Bullet*>(object.get()) ||
			dynamic_cast<BlueTank*>(object.get()))
		{
			GetScene()->Remove(object);
		}
	}
}


bool Level::CollisionHit(GameObject* object, const glm::vec2& dir)
{
	//make diff collisions for tank and bullet
	const auto objectPos = object->GetWorldTransform();

	//const std::vector<glm::vec2> cornerPoints = 
	//{ 
	//	{objectPos.x, objectPos.y}, //topLeft
	//	{objectPos.x , objectPos.y + object->GetSize().y / 2}, //bottomLeft
	//	{objectPos.x + object->GetSize().x / 2, objectPos.y}, //topRight
	//	{objectPos.x + object->GetSize().x / 2, objectPos.y + object->GetSize().y / 2} //bottomRight
	//};
	//const float rayLength = 1;
	//std::vector<glm::vec2> rayPoints{};
	//for (auto p : cornerPoints)
	//{
	//	rayPoints.push_back({p.x + dir.x * rayLength, p.y + dir.y * rayLength});
	//}
	const glm::vec2 midPoint = { objectPos.x + object->GetSize().x / 2, objectPos.y + object->GetSize().y / 2 };
	const float rayLength = object->GetSize().x / 2;
	const float dirLength = sqrtf(dir.x * dir.x + dir.y * dir.y);
	const glm::vec3 normalizedDir = { dir.x / dirLength,  dir.y / dirLength, 0 };
	const glm::vec2 rayPoint = { midPoint.x + normalizedDir.x * rayLength, midPoint.y + normalizedDir.y * rayLength };

	if (dynamic_cast<Tank*>(object) && CheckTeleportCollision(rayPoint))
	{
		object->SetRelativePos(GetRandomSpawnPos());
		return false;
	}

	for (const auto& wall : m_pWalls)
	{
		//if (wall->GetTag() != "Wall") continue;

		//possible improvement: not every corner needs to check every direction (bottomLeft doesnt need to check right/down, etc...
		/*for (auto r : rayPoints)
		{
			if (r.x > wall->GetWorldTransform().x && r.x < wall->GetWorldTransform().x + wall->GetSize().x &&
				r.y > wall->GetWorldTransform().y && r.y < wall->GetWorldTransform().y + wall->GetSize().y)
			{
				return false;
			}
		}*/

		if (rayPoint.x >= wall->GetWorldTransform().x && rayPoint.x <= wall->GetWorldTransform().x + wall->GetSize().x &&
			rayPoint.y >= wall->GetWorldTransform().y && rayPoint.y <= wall->GetWorldTransform().y + wall->GetSize().y)
		{
			return true;
		}
	}

	return false;
}


void Level::UpdateBullets()
{
	for (auto& o : GetScene()->GetGameObjects())
	{
		if (!dynamic_cast<Bullet*>(o.get())) continue;

		auto pBullet = static_cast<Bullet*>(o.get());

		if (CollisionHit(pBullet, pBullet->GetVelocity()))
		{
			pBullet->SetVelocity(-pBullet->GetVelocity());
		}
	}
}

bool Level::CheckTeleportCollision(const glm::vec2& rayPoint)
{
	for (const auto& wall : m_pTeleport)
	{
		if (rayPoint.x >= wall->GetWorldTransform().x && rayPoint.x <= wall->GetWorldTransform().x + wall->GetSize().x &&
			rayPoint.y >= wall->GetWorldTransform().y && rayPoint.y <= wall->GetWorldTransform().y + wall->GetSize().y)
		{
			return true;
		}
	}
	return false;
}


