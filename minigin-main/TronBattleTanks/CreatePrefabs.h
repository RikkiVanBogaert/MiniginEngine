#pragma once
#include "BulletManagerCp.h"
#include "CollisionCp.h"
#include "GameObject.h"
#include "SpawnPositionCp.h"
#include "TextureComponent.h"
#include "InputManager.h"
#include "ResourceManager.h"

using namespace dae;

static GameObject* CreateBullet(Scene& scene);


static void CreateTank(Scene& scene)
{
	auto pTank = std::make_shared<dae::GameObject>();
	scene.Add(pTank);
	PlayerManager::GetInstance().AddPlayer(pTank);

	//Texture
	auto tankTxt = std::make_shared<dae::TextureComponent>(pTank.get());
	tankTxt->SetTexture("Resources/Sprites/RedTank.png");
	pTank->AddComponent(tankTxt);

	//BulletManager
	auto bulletManager = std::make_shared<BulletManagerCp>(pTank.get());
	pTank->AddComponent(bulletManager);
	for (int i{}; i < 3; ++i)
	{
		bulletManager->AddBullet(CreateBullet(scene));
	}

	//Movement
	constexpr float speed{ 1.5f };
	glm::vec3 up = { 0.f,-speed,0.f };
	glm::vec3 down = { 0.f,speed,0.f };
	glm::vec3 right = { speed,0.f,0.f };
	glm::vec3 left = { -speed,0.f,0.f };

	auto* moveCommandUp = new MoveCommand{ pTank.get(), up };
	auto* moveCommandDown = new MoveCommand{ pTank.get(), down };
	auto* moveCommandLeft = new MoveCommand{ pTank.get(), left };
	auto* moveCommandRight = new MoveCommand{ pTank.get(), right };

	dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_S, moveCommandDown);
	dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_W, moveCommandUp);
	dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_A, moveCommandLeft);
	dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_D, moveCommandRight);

	//Shooting
	const float shootSpeed{ 300 };
	glm::vec3 shootUpSpeed = { 0.f, -shootSpeed, 0.f };
	glm::vec3 shootDownSpeed = { 0.f, shootSpeed, 0.f };
	glm::vec3 shootLeftSpeed = { -shootSpeed, 0.f, 0.f };
	glm::vec3 shootRightSpeed = { shootSpeed, 0.f, 0.f };

	auto* shootUp = new ShootCommand{ pTank.get(), shootUpSpeed };
	auto* shootDown = new ShootCommand{ pTank.get(), shootDownSpeed };
	auto* shootLeft = new ShootCommand{ pTank.get(), shootLeftSpeed };
	auto* shootRight = new ShootCommand{ pTank.get(), shootRightSpeed };

	InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_UP, shootUp);
	InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_DOWN, shootDown);
	InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_LEFT, shootLeft);
	InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_RIGHT, shootRight);
}

static GameObject* CreateBullet(Scene& scene)
{
	auto pBullet = std::make_shared<dae::GameObject>();
	scene.Add(pBullet);

	const auto bulletTxt = std::make_shared<TextureComponent>(pBullet.get());
	bulletTxt->SetTexture("Resources/Sprites/BulletPlayer.png");
	pBullet->AddComponent(bulletTxt);

	return pBullet.get();
}

static std::shared_ptr<GameObject> CreateLevel(Scene& scene, const std::string& levelPath)
{
	auto pLevelObject = std::make_shared<GameObject>();
	scene.Add(pLevelObject);
	pLevelObject->SetTag("Level");

	auto collisionCp = std::make_shared<CollisionCp>(pLevelObject.get());
	pLevelObject->AddComponent(collisionCp);

	auto spawnPosCp = std::make_shared<SpawnPositionCp>(pLevelObject.get());
	pLevelObject->AddComponent(spawnPosCp);

	constexpr int columns = 58;
	auto map = ResourceManager::GetInstance().ParseCsv(levelPath);
	constexpr float size{ 8 };
	constexpr glm::vec2 startPos{ 100,20 };
	glm::vec2 pos{ startPos };
	int amountSpawnPos{};
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
			pBlock->SetTag("Wall");

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
			++amountSpawnPos;
			if(amountSpawnPos == 1 || amountSpawnPos == 5)
				spawnPosCp->AddPos(pos);
			break;
		case 6:
			//m_SpawnPosPlayers.push_back({ pos.x - offset.x, pos.y - offset.y });
			break;
		default:
			//m_pPaths.push_back(pBlock.get());
			break;
		}


		//m_pLevelObjects.push_back(std::move(pBlock));

		pos.x += size;

		if ((i + 1) % columns == 0)
		{
			pos.x = startPos.x;
			pos.y += size;
		}
	}

	return pLevelObject;
}

static void CreateMainMenu(Scene& scene)
{
	auto pMenuObj = std::make_shared<GameObject>();
	scene.Add(pMenuObj);

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto smallFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);

	const auto startObj = std::make_shared<GameObject>();
	const auto startText = std::make_shared<TextComponent>(startObj.get(), "START (Space)", font, SDL_Color{ 255, 255, 255 });
	startObj->SetRelativePos({ 200, 40 });
	startObj->AddComponent(startText);
	pMenuObj->AddChild(startObj);


	const auto quitObj = std::make_shared<GameObject>();
	const auto quitText = std::make_shared<TextComponent>(quitObj.get(), "QUIT (Esc)", font, SDL_Color{ 255, 255, 255 });
	quitObj->SetRelativePos({ 230, 160 });
	quitObj->AddComponent(quitText);
	pMenuObj->AddChild(quitObj);

	const auto switchGameModeObj = std::make_shared<GameObject>();
	const auto switchGameModeText = std::make_shared<TextComponent>(switchGameModeObj.get(), "Switch GameMode (Shift)", font, SDL_Color{ 255, 255, 255 });
	switchGameModeObj->SetRelativePos({ 140, 280 });
	switchGameModeObj->AddComponent(switchGameModeText);
	pMenuObj->AddChild(switchGameModeObj);

	const auto m_pGameModeObject = std::make_shared<GameObject>();
	m_pGameModeObject->SetTag("GameMode");
	auto m_pGameModeText = std::make_shared<TextComponent>(m_pGameModeObject.get(), "SinglePlayer", smallFont, SDL_Color{ 255, 255, 255 });
	m_pGameModeObject->SetRelativePos({ 190, 320 });
	m_pGameModeObject->AddComponent(m_pGameModeText);
	pMenuObj->AddChild(m_pGameModeObject);


	const auto nextLevelObj = std::make_shared<GameObject>();
	const auto nextLevelText = std::make_shared<TextComponent>(nextLevelObj.get(), "Next Level (N)", smallFont, SDL_Color{ 255, 255, 255 });
	nextLevelObj->SetRelativePos({ 10, 430 });
	nextLevelObj->AddComponent(nextLevelText);
	pMenuObj->AddChild(nextLevelObj);
}