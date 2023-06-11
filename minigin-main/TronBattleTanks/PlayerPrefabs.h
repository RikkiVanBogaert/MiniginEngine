#pragma once
#include <SDL_scancode.h>
#include <glm/vec3.hpp>

#include "BulletCollisionCp.h"
#include "BulletManagerCp.h"
#include "CollisionCp.h"
#include "GameCommands.h"
#include "InputManager.h"
#include "MoveCp.h"
#include "GameManager.h"
#include "Scene.h"
#include "TextureComponent.h"
#include "GunPrefab.h"
#include "PlayerLivesCp.h"
#include "PlayerManager.h"
#include "PointsCp.h"

static void CreateTankKeyboardAndController(dae::Scene& scene)
{
	const auto pTank = std::make_shared<dae::GameObject>();
	scene.Add(pTank);
	PlayerManager::GetInstance().AddPlayer(pTank);

	//Texture
	const auto tankTxt = std::make_shared<dae::TextureComponent>(pTank.get());
	tankTxt->SetTexture("Resources/Sprites/RedTank.png");
	pTank->AddComponent(tankTxt);

	//Collision
	const auto collisionCp = std::make_shared<CollisionCp>(pTank.get());
	pTank->AddComponent(collisionCp);
	collisionCp->AddCollider(pTank.get());

	const auto bulletCollisionCp = std::make_shared<BulletCollisionCp>(pTank.get());
	pTank->AddComponent(bulletCollisionCp);


	//Points
	const auto points = std::make_shared<PointsCp>(pTank.get(), 0);
	pTank->AddComponent(points);

	//Health
	const auto health = std::make_shared<PlayerLivesCp>(pTank.get(), 3);
	pTank->AddComponent(health);


	//Create Controller
	int controllerIdx{ GameManager::GetInstance().GetControllerIdx() };
	dae::InputManager::GetInstance().AddController(controllerIdx);
	++GameManager::GetInstance().GetControllerIdx();

	//Movement
	const auto moveCp = std::make_shared<MoveCp>(pTank.get(), 65.f);
	pTank->AddComponent(moveCp);

	constexpr float speed{ 1.5f };
	glm::vec3 up = { 0.f,-speed,0.f };
	glm::vec3 down = { 0.f,speed,0.f };
	glm::vec3 right = { speed,0.f,0.f };
	glm::vec3 left = { -speed,0.f,0.f };

	const auto moveCommandUp = std::make_shared<MoveCommand>(pTank.get(), up);
	const auto moveCommandDown = std::make_shared<MoveCommand>(pTank.get(), down);
	const auto moveCommandLeft = std::make_shared<MoveCommand>(pTank.get(), left);
	const auto moveCommandRight = std::make_shared<MoveCommand>(pTank.get(), right, controllerIdx);

	dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_W, moveCommandUp);
	dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_S, moveCommandDown);
	dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_A, moveCommandLeft);
	dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_D, moveCommandRight);

	dae::Controller::ControllerStick t = dae::Controller::ControllerStick::LeftStick;
	dae::InputManager::GetInstance().BindControllerToCommand(controllerIdx, t, moveCommandRight);


	//Gun-Shooting
	const auto pGun = CreateTankGun(scene, controllerIdx);
	pGun->SetTag(pTank->GetTag());
	pTank->AddChild(pGun);

	pTank->SetTagIncludingChildren("RedPlayer");
}

static void CreateTankController(dae::Scene& scene)
{
	const auto pTank = std::make_shared<dae::GameObject>();
	scene.Add(pTank);
	PlayerManager::GetInstance().AddPlayer(pTank);

	//Texture
	const auto tankTxt = std::make_shared<dae::TextureComponent>(pTank.get());
	tankTxt->SetTexture("Resources/Sprites/RedTank.png");
	pTank->AddComponent(tankTxt);

	//Collision
	const auto collisionCp = std::make_shared<CollisionCp>(pTank.get());
	pTank->AddComponent(collisionCp);
	collisionCp->AddCollider(pTank.get());

	const auto bulletCollisionCp = std::make_shared<BulletCollisionCp>(pTank.get());
	pTank->AddComponent(bulletCollisionCp);

	//Points
	const auto points = std::make_shared<PointsCp>(pTank.get(), 0);
	pTank->AddComponent(points);

	//Health
	const auto health = std::make_shared<PlayerLivesCp>(pTank.get(), 3);
	pTank->AddComponent(health);


	//Create Controller
	int controllerIdx{ GameManager::GetInstance().GetControllerIdx() };
	dae::InputManager::GetInstance().AddController(controllerIdx);
	++GameManager::GetInstance().GetControllerIdx();


	//Movement
	const auto moveCp = std::make_shared<MoveCp>(pTank.get(), 65.f);
	pTank->AddComponent(moveCp);

	constexpr float speed{ 1.5f };
	glm::vec3 up = { 0.f,-speed,0.f };
	glm::vec3 down = { 0.f,speed,0.f };
	glm::vec3 right = { speed,0.f,0.f };
	glm::vec3 left = { -speed,0.f,0.f };

	const auto moveCommandUp = std::make_shared<MoveCommand>(pTank.get(), up);
	const auto moveCommandDown = std::make_shared<MoveCommand>(pTank.get(), down);
	const auto moveCommandLeft = std::make_shared<MoveCommand>(pTank.get(), left);
	const auto moveCommandRight = std::make_shared<MoveCommand>(pTank.get(), right, controllerIdx);

	dae::Controller::ControllerStick t = dae::Controller::ControllerStick::LeftStick;
	dae::InputManager::GetInstance().BindControllerToCommand(controllerIdx, t, moveCommandRight);


	//Gun-Shooting
	const auto pGun = CreateTankGun(scene, controllerIdx, false);
	pGun->SetTag(pTank->GetTag());
	pTank->AddChild(pGun);

	pTank->SetTagIncludingChildren("RedPlayer");
}
