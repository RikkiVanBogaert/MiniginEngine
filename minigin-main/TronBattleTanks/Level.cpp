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
	m_pScene = scene;
	CreateMap(map, 58);
	//ResetLevel();
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
		case 6:
			if(m_SpawnPos.y == 0)
				m_SpawnPos = { pos };
			//intentional no break
			pTexture->SetTexture("Resources/Level/teleport.png");
			break;
		default:
			pTexture->SetTexture("Resources/Level/path.png");
			pBlock->SetTag("Path");
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

void Level::LoadCharacters()
{
	glm::vec3 up = { 0.f,-1.f,0.f };
	glm::vec3 down = { 0.f,1.f,0.f };
	glm::vec3 right = { 1.f,0.f,0.f };
	glm::vec3 left = { -1.f,0.f,0.f };
	//int controllerIdx{ 0 };

	auto fontTankUI = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 15);

	//PREFAB RED TANK
	{
		auto tankPrefab = std::make_shared<RedTank>();
		AddChild(tankPrefab.get());
		tankPrefab->SetRelativePos({ 230, 355 });
		tankPrefab->SetScene(GetScene());

		MoveCommand* moveCommandUp = new MoveCommand{ tankPrefab.get(), up };
		MoveCommand* moveCommandDown = new MoveCommand{ tankPrefab.get(), down };
		MoveCommand* moveCommandLeft = new MoveCommand{ tankPrefab.get(), left };
		MoveCommand* moveCommandRight = new MoveCommand{ tankPrefab.get(), right };

		dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_S, moveCommandDown);
		dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_W, moveCommandUp);
		dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_A, moveCommandLeft);
		dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_D, moveCommandRight);

		//Shooting
		const float shootSpeed{ 300.f };
		up = { 0.f, -shootSpeed, 0.f };
		down = { 0.f, shootSpeed, 0.f };
		left = { -shootSpeed, 0.f, 0.f };
		right = { shootSpeed, 0.f, 0.f };
		ShootCommand* shootUp = new ShootCommand{ tankPrefab.get(), up };
		ShootCommand* shootDown = new ShootCommand{ tankPrefab.get(), down };
		ShootCommand* shootLeft = new ShootCommand{ tankPrefab.get(), left };
		ShootCommand* shootRight = new ShootCommand{ tankPrefab.get(), right };

		dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_UP, shootUp);
		dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_DOWN, shootDown);
		dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_LEFT, shootLeft);
		dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_RIGHT, shootRight);

		GetScene()->Add(tankPrefab);



		////Dying/Points logic
		//auto pHealth = std::make_shared<dae::HealthCp>(tankPrefab.get(), 1);
		//tankPrefab->AddComponent(pHealth);

		//auto pPoints = std::make_shared<dae::PointsCp>(tankPrefab.get(), 0);
		//tankPrefab->AddComponent(pPoints);

		//DieCommand* dieCommand = new DieCommand{ tankPrefab.get() };
		//dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_O, dieCommand);
		//PointCommand* pointCommand = new PointCommand{ tankPrefab.get() };
		//dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_P, pointCommand);

		//auto pUIObserver = std::make_shared<UI>();
		//tankPrefab->MakeObserver(pUIObserver);

		//
		////Lives Display
		//auto redTankLivesObj = std::make_shared<GameObject>("redTank");
		//auto textRedLives = std::make_shared <dae::UICp> (fontTankUI, "Lives: ", SDL_Color{ 255, 0, 0 },
		//	"Lives", redTankLivesObj.get());
		//redTankLivesObj->SetRelativePos({ 5, 310, 0 });
		//redTankLivesObj->AddComponent(textRedLives);
		//AddChild(redTankLivesObj.get());
		//GetScene()->Add(redTankLivesObj);

		////Points Display
		//auto redTankPointsObj = std::make_shared<GameObject>("redTank");
		//auto textBluePoints = std::make_shared<dae::UICp>(fontTankUI, "Points: ", SDL_Color{ 255, 0, 0 },
		//	"Points", redTankPointsObj.get());
		//redTankPointsObj->SetRelativePos({ 5, 340, 0 });
		//redTankPointsObj->AddComponent(textBluePoints);
		//AddChild(redTankPointsObj.get());
		//GetScene()->Add(redTankPointsObj);
		//
	}

	////BLUE TANK
	//{
	//	glm::vec3 downBlue = { 0.f,2.f,0.f };
	//	glm::vec3 upBlue = { 0.f,-2.f,0.f };
	//	glm::vec3 leftBlue = { -2.f,0.f,0.f };
	//	glm::vec3 rightBlue = { 2.f,0.f,0.f };

	//	auto blueTank = std::make_shared<BlueTank>();
	//	blueTank->SetRelativePos({ 330, 250, 0 });

	//	MoveCommand* moveCommandDownBlue = new MoveCommand{ blueTank.get(), downBlue };
	//	MoveCommand* moveCommandUpBlue = new MoveCommand{ blueTank.get(), upBlue };
	//	MoveCommand* moveCommandLeftBlue = new MoveCommand{ blueTank.get(), leftBlue };
	//	MoveCommand* moveCommandRightBlue = new MoveCommand{ blueTank.get(), rightBlue };

	//	dae::InputManager::GetInstance().AddController(controllerIdx);

	//	Controller::ControllerButton button{};

	//	button = Controller::ControllerButton::DpadDown;
	//	dae::InputManager::GetInstance().BindControllerToCommand(controllerIdx, button, moveCommandDownBlue);
	//	button = Controller::ControllerButton::DpadUp;
	//	dae::InputManager::GetInstance().BindControllerToCommand(controllerIdx, button, moveCommandUpBlue);
	//	button = Controller::ControllerButton::DpadLeft;
	//	dae::InputManager::GetInstance().BindControllerToCommand(controllerIdx, button, moveCommandLeftBlue);
	//	button = Controller::ControllerButton::DpadRight;
	//	dae::InputManager::GetInstance().BindControllerToCommand(controllerIdx, button, moveCommandRightBlue);

	//	scene.Add(blueTank);

	//	//Dying/Points logic
	//	auto pHealthBlue = std::make_shared<HealthCp>(blueTank.get(), 1);
	//	blueTank->AddComponent(pHealthBlue);

	//	auto pPointsBlue = std::make_shared<PointsCp>(blueTank.get(), 0);
	//	blueTank->AddComponent(pPointsBlue);

	//	DieCommand* dieCommandBlue = new DieCommand{ blueTank.get() };
	//	button = Controller::ControllerButton::ButtonY;
	//	dae::InputManager::GetInstance().BindControllerToCommand(controllerIdx, button, dieCommandBlue);
	//	PointCommand* pointCommandBlue = new PointCommand{ blueTank.get() };
	//	button = Controller::ControllerButton::ButtonA;
	//	dae::InputManager::GetInstance().BindControllerToCommand(controllerIdx, button, pointCommandBlue);

	//	auto pUIObserverBlue = std::make_shared<UI>();
	//	blueTank->MakeObserver(pUIObserverBlue);

	//	parent->AddChild(blueTank.get());
	//	scene.Add(blueTank);

	//	//Lives Display
	//	auto blueTankLivesObj = std::make_shared<GameObject>("blueTank");
	//	auto textBlueLives = std::make_shared<UICp>(fontTankUI, "Lives: ", SDL_Color{ 0, 0, 255 },
	//		"Lives", blueTankLivesObj.get());
	//	blueTankLivesObj->SetRelativePos({ 5, 380, 0 });
	//	blueTankLivesObj->AddComponent(textBlueLives);
	//	parent->AddChild(blueTankLivesObj.get());
	//	scene.Add(blueTankLivesObj);

	//	//Points Display
	//	auto blueTankPointsObj = std::make_shared<GameObject>("blueTank");
	//	auto textBluePoints = std::make_shared<UICp>(fontTankUI, "Points: ", SDL_Color{ 0, 0, 255 },
	//		"Points", blueTankPointsObj.get());
	//	blueTankPointsObj->SetRelativePos({ 5, 410, 0 });
	//	blueTankPointsObj->AddComponent(textBluePoints);
	//	parent->AddChild(blueTankPointsObj.get());
	//	scene.Add(blueTankPointsObj);
	//}
}

void Level::OnLevelLoad()
{	
	auto player = PlayerManager::getInstance().GetPlayers()[0];
	player->SetRelativePos(m_SpawnPos);

	player->GetScene()->Remove(player);
	GetScene()->Add(player);
}

void Level::OnLevelDestroy()
{
	for (auto& object : GetScene()->GetGameObjects())
	{
		if (dynamic_cast<Bullet*>(object.get()))
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

		if (rayPoint.x > wall->GetWorldTransform().x && rayPoint.x < wall->GetWorldTransform().x + wall->GetSize().x &&
			rayPoint.y > wall->GetWorldTransform().y && rayPoint.y < wall->GetWorldTransform().y + wall->GetSize().y)
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
		if (rayPoint.x > wall->GetWorldTransform().x && rayPoint.x < wall->GetWorldTransform().x + wall->GetSize().x &&
			rayPoint.y > wall->GetWorldTransform().y && rayPoint.y < wall->GetWorldTransform().y + wall->GetSize().y)
		{
			return true;
		}
	}
	return false;
}



void Level::SetScene(dae::Scene* scene)
{
	m_pScene = scene;
}

dae::Scene* Level::GetScene()
{
	return m_pScene;
}