#include "Level.h"
#include "Scene.h"
#include "Bullet.h"


using namespace std;

Level::Level(std::vector<int> map)
{
	CreateMap(map);
}

void Level::Update(float)
{
	UpdateBullets();
}

bool Level::CollisionHit(GameObject* object, const glm::vec3& dir)
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
	const glm::vec2 midPoint = {objectPos.x + object->GetSize().x / 2, objectPos.y + object->GetSize().y / 2};
	const float rayLength = object->GetSize().x / 2;
	const float dirLength = sqrtf(dir.x * dir.x + dir.y * dir.y);
	const glm::vec3 normalizedDir = { dir.x / dirLength,  dir.y / dirLength, 0 };
	const glm::vec2 rayPoint = { midPoint.x + normalizedDir.x * rayLength, midPoint.y + normalizedDir.y * rayLength };

	for (const auto& wall : m_pBlocks)
	{
		if (wall->GetTag() != "Wall") continue;

		//possible improvement: not every corner needs to check every direction (bottomLeft doesnt need to check right/down, etc...
		/*for (auto r : rayPoints)
		{
			if (r.x > wall->GetWorldTransform().x && r.x < wall->GetWorldTransform().x + wall->GetSize().x &&
				r.y > wall->GetWorldTransform().y && r.y < wall->GetWorldTransform().y + wall->GetSize().y)
			{
				return false;
			}
		}*/

		if (rayPoint.x > wall->GetWorldTransform().x && rayPoint.x < wall->GetWorldTransform().x + wall->GetSize().x &&
			rayPoint.y > wall->GetWorldTransform().y && rayPoint.y < wall->GetWorldTransform().y + wall->GetSize().y)
		{
			return true;
		}
	}

	return false;
}


void Level::CreateMap(std::vector<int> map)
{
	//auto map = parse_csv(mapFile);

	//const int rows{54};
	const int cols{ 58 };
	const float size{ 8 };
	const glm::vec2 startPos{ 100,10 };
	glm::vec2 pos{ startPos };
	for (int i{}; i < map.size(); ++i)
	{
		auto pBlock = std::make_unique<GameObject>();
		auto pTexture = std::make_shared<TextureComponent>(pBlock.get());
		AddChild(pBlock.get());
		pBlock->SetRelativePos({ pos.x, pos.y, 0 });
		pBlock->SetSize({ size, size });
		pBlock->AddComponent(pTexture);
		switch (map[i])
		{
		case 0:
			pTexture->SetTexture("Resources/Level/wall.png");
			pBlock->SetTag("Wall");
			break;
		case 1:
			pTexture->SetTexture("Resources/Level/void.png");
			break;
		default:
			pTexture->SetTexture("Resources/Level/path.png");
			pBlock->SetTag("Path");
			break;
		}


		m_pBlocks.push_back(std::move(pBlock));

		pos.x += size;

		if ((i + 1) % cols == 0)
		{
			pos.x = startPos.x;
			pos.y += size;
		}
	}
}

glm::vec3 Level::GetRandomSpawnPos() const
{
	std::vector<int> pathIndexes{};
	for (int i{}; i < m_pBlocks.size(); ++i)
	{
		if (m_pBlocks[i]->GetTag() != "Path") continue;

		pathIndexes.push_back(i);
	}

	const int rndIndex = rand() % (pathIndexes.size() + 1);
	const auto spawnPos = m_pBlocks[rndIndex]->GetWorldTransform();

	return spawnPos;
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
