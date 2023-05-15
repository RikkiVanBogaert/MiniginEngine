#include "Level.h"
#include "ResourceManager.h"
#include "Scene.h"

//Components
#include "TextComponent.h"
#include "TextureComponent.h"
#include "UICp.h"

#include "GameObject.h"
#include "InputManager.h"

#include "Tank.h"
#include "Bullet.h"

#include "PlayerManager.h"

using namespace dae;

Level::Level(const std::vector<int>& map, dae::Scene* scene)
{
	SetScene(scene);
	CreateMap(map, 58);
}

void Level::Update(float)
{
	UpdateBullets();
}


void Level::CreateMap(const std::vector<int>& map, int columns)
{
	constexpr float size{ 8 };
	constexpr glm::vec2 startPos{ 100,20 };
	glm::vec2 pos{ startPos };
	for (size_t i{}; i < map.size(); ++i)
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
			m_SpawnPosPlayers.push_back({ pos.x - offset.x, pos.y - offset.y });
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

void Level::InitHUDSinglePlayer()
{
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);

	//Points
	auto pPointText = std::make_shared<GameObject>("redTank");
	auto pPointsCounterPlayer = PlayerManager::GetInstance().GetPlayers()[0]->GetComponent<PointsCp>();
	const auto text = std::make_shared<UICounterCp>(pPointText.get(), font, "Points: ", SDL_Color{ 255, 0, 0 }, pPointsCounterPlayer);
	pPointText->AddComponent(text);
	pPointText->SetRelativePos({ 5, 310 });
	GetScene()->Add(pPointText);

	//Lives
	auto pLivesText = std::make_shared<GameObject>("redTank");
	auto pLivesCounterPlayer = PlayerManager::GetInstance().GetPlayers()[0]->GetComponent<HealthCp>();
	const auto textLives = std::make_shared<UICounterCp>(pLivesText.get(), font, "Lives: ", SDL_Color{ 255, 0, 0 }, pLivesCounterPlayer);
	pLivesText->AddComponent(textLives);
	pLivesText->SetRelativePos({ 5, 360 });
	GetScene()->Add(pLivesText);
}

void Level::InitHUDVersus()
{
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);

	//Player 1
	{
		//Points
		auto pPointText = std::make_shared<GameObject>("Red");
		auto pPointsCounterPlayer = PlayerManager::GetInstance().GetPlayers()[0]->GetComponent<PointsCp>();
		const auto text = std::make_shared<UICounterCp>(pPointText.get(), font, "Points: ", SDL_Color{ 255, 0, 0 }, pPointsCounterPlayer);
		pPointText->AddComponent(text);
		pPointText->SetRelativePos({ 5, 210 });
		GetScene()->Add(pPointText);

		//Lives
		auto pLivesText = std::make_shared<GameObject>("Red");
		auto pLivesCounterPlayer = PlayerManager::GetInstance().GetPlayers()[0]->GetComponent<HealthCp>();
		const auto textLives = std::make_shared<UICounterCp>(pLivesText.get(), font, "Lives: ", SDL_Color{ 255, 0, 0 }, pLivesCounterPlayer);
		pLivesText->AddComponent(textLives);
		pLivesText->SetRelativePos({ 5, 260 });
		GetScene()->Add(pLivesText);
	}

	//Player 2
	{
		//Points
		auto pPointText = std::make_shared<GameObject>("Blue");
		auto pPointsCounterPlayer = PlayerManager::GetInstance().GetPlayers()[0]->GetComponent<PointsCp>();
		const auto text = std::make_shared<UICounterCp>(pPointText.get(), font, "Points: ", SDL_Color{ 0, 0, 255 }, pPointsCounterPlayer);
		pPointText->AddComponent(text);
		pPointText->SetRelativePos({ 5, 310 });
		GetScene()->Add(pPointText);

		//Lives
		auto pLivesText = std::make_shared<GameObject>("Blue");
		auto pLivesCounterPlayer = PlayerManager::GetInstance().GetPlayers()[1]->GetComponent<HealthCp>();
		const auto textLives = std::make_shared<UICounterCp>(pLivesText.get(), font, "Lives: ", SDL_Color{ 0, 0, 255 }, pLivesCounterPlayer);
		pLivesText->AddComponent(textLives);
		pLivesText->SetRelativePos({ 5, 360 });
		GetScene()->Add(pLivesText);
	}
}

glm::vec2 Level::GetRandomSpawnPos() const
{
	const auto rndIndex = rand() % (m_pPaths.size() + 1);
	const auto spawnPos = m_pPaths[rndIndex]->GetWorldTransform();

	return spawnPos;
}

void Level::OnLevelLoad()
{	

	switch (PlayerManager::GetInstance().GetGameMode())
	{
	case PlayerManager::SinglePlayer:
		LoadSinglePlayer();
		InitHUDSinglePlayer();
		break;
	case PlayerManager::Coop:
		LoadCoop();
		break;
	case PlayerManager::Versus:
		LoadVersus();
		InitHUDVersus();
		break;
	}

}

void Level::LoadSinglePlayer() const
{
	//Player----
	const auto player = PlayerManager::GetInstance().GetPlayers()[0];
	for (size_t i{}; i < m_SpawnPosPlayers.size(); i += 4)
	{
		player->SetRelativePos(m_SpawnPosPlayers[i]);
		GetScene()->Add(player);
	}

	player->GetScene()->Remove(player);
	GetScene()->Add(player);

	//Enemies----
	for (size_t i{}; i < m_SpawnPosBlueTanks.size(); i += 4)
	{
		auto blueTank = std::make_shared<EnemyTank>();
		blueTank->SetRelativePos(m_SpawnPosBlueTanks[i]);
		GetScene()->Add(blueTank);
	}
}

void Level::LoadCoop() const
{
	//Players----
	const auto player = PlayerManager::GetInstance().GetPlayers()[0];
	const auto player2 = PlayerManager::GetInstance().GetPlayers()[1];
	for (size_t i{}; i < m_SpawnPosPlayers.size(); i += 4)
	{
		if (i == 0)
		{
			player->SetRelativePos(m_SpawnPosPlayers[i]);
			GetScene()->Add(player);
		}
		else
		{
			player2->SetRelativePos(m_SpawnPosPlayers[i]);
			GetScene()->Add(player2);
		}
	}

	player->GetScene()->Remove(player);
	GetScene()->Add(player);

	player2->GetScene()->Remove(player2);
	GetScene()->Add(player2);

	player2->SetTag("Red");
	const auto pTexture = player2->GetComponent<TextureComponent>();
	pTexture->SetTexture("Resources/Sprites/RedTank.png");


	//Enemies----
	for (size_t i{}; i < m_SpawnPosBlueTanks.size(); i += 4)
	{
		auto blueTank = std::make_shared<EnemyTank>();
		blueTank->SetRelativePos(m_SpawnPosBlueTanks[i]);
		GetScene()->Add(blueTank);
	}
}

void Level::LoadVersus() const
{
	//Players----
	const auto player = PlayerManager::GetInstance().GetPlayers()[0];
	const auto player2 = PlayerManager::GetInstance().GetPlayers()[1];
	for (size_t i{}; i < m_SpawnPosPlayers.size(); i += 4)
	{
		if (i == 0)
		{
			player->SetRelativePos(m_SpawnPosPlayers[i]);
			GetScene()->Add(player);
		}
		else
		{
			player2->SetRelativePos(m_SpawnPosPlayers[i]);
			GetScene()->Add(player2);
		}
	}

	player->GetScene()->Remove(player);
	GetScene()->Add(player);

	player2->GetScene()->Remove(player2);
	GetScene()->Add(player2);

	player2->SetTag("Blue");
	const auto pTexture = player2->GetComponent<TextureComponent>();
	pTexture->SetTexture("Resources/Sprites/BlueTank.png");
}

void Level::OnLevelDestroy()
{
	for (auto& object : GetScene()->GetGameObjects())
	{
		if (dynamic_cast<Bullet*>(object.get()) ||
			dynamic_cast<EnemyTank*>(object.get()))
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
	const glm::vec2 normalizedDir = { dir.x / dirLength,  dir.y / dirLength };
	const glm::vec2 rayPoint = { midPoint.x + normalizedDir.x * rayLength, midPoint.y + normalizedDir.y * rayLength };

	if (dynamic_cast<Tank*>(object) && CheckTeleportCollision(rayPoint))
	{
		object->SetRelativePos(GetRandomSpawnPos());
		return false;
	}

	for (const auto& wall : m_pWalls)
	{
		/*if (wall->GetTag() != "Wall") continue;
		possible improvement: not every corner needs to check every direction (bottomLeft doesnt need to check right/down, etc...
		for (auto r : rayPoints)
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

bool Level::HitWall(const glm::vec2& start, const glm::vec2& end)
{
	//First check if start is in a straight line with the end with a certain offset (size tank);
	//if true => check if there are intersecting walls

	const float playerSize{ 16 };
	const glm::vec2 tankMidPos{ start.x + playerSize / 2, start.y + playerSize / 2 };

	//Straight line
	if (!(tankMidPos.x > end.x && tankMidPos.x < end.x + playerSize)
		&& !(tankMidPos.y > end.y && tankMidPos.y < end.y + playerSize))
		return true;


	// Calculate vector L between start and end points
	float Lx = end.x - start.x;
	float Ly = end.y - start.y;
	// Calculate length of vector L
	float lengthL = std::sqrt(Lx * Lx + Ly * Ly);

	// Normalize vector L
	Lx /= lengthL;
	Ly /= lengthL;

	for (const auto& wall : m_pWalls)
	{
		// Calculate vector S between start point and square center
		float Sx = wall->GetRelativeTransform().x - start.x;
		float Sy = wall->GetRelativeTransform().y - start.y;

		// Calculate distance between start point and square center
		//double distanceS = std::sqrt(Sx * Sx + Sy * Sy);

		// Calculate projection of vector S onto vector L
		float projectionSL = Sx * Lx + Sy * Ly;

		// Check if square is on the line between start and end points
		if (projectionSL < 0 || projectionSL > lengthL) 
		{
			continue;
		}

		// Check if square intersects with line segment
		float distanceThreshold = wall->GetSize().x / 2; // adjust as needed
		float distanceToLine = std::abs((Sx * Ly) - (Sy * Lx));

		if (distanceToLine <= distanceThreshold)
			return true;
	}

	return false;
}


void Level::UpdateBullets()
{
	for (auto& o : GetScene()->GetGameObjects())
	{
		if (!dynamic_cast<Bullet*>(o.get())) continue;

		const auto pBullet = dynamic_cast<Bullet*>(o.get());

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


