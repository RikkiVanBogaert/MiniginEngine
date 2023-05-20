#pragma once
#include <SDL_scancode.h>
#include <glm/vec3.hpp>

#include "BulletCollisionCp.h"
#include "BulletManagerCp.h"
#include "CollisionCp.h"
#include "GameCommands.h"
#include "InputManager.h"
#include "PlayerManager.h"
#include "Scene.h"
#include "TextureComponent.h"

using namespace dae;

static void CreateTankKeyboard(Scene& scene)
{
	auto pTank = std::make_shared<dae::GameObject>();
	scene.Add(pTank);
	pTank->SetTag("RedPlayer");
	PlayerManager::GetInstance().AddPlayer(pTank);

	//Texture
	auto tankTxt = std::make_shared<dae::TextureComponent>(pTank.get());
	tankTxt->SetTexture("Resources/Sprites/RedTank.png");
	pTank->AddComponent(tankTxt);

	//Collision
	auto collisionCp = std::make_shared<CollisionCp>(pTank.get());
	pTank->AddComponent(collisionCp);
	collisionCp->AddCollider(pTank.get());

	auto bulletCollisionCp = std::make_shared<BulletCollisionCp>(pTank.get());
	pTank->AddComponent(bulletCollisionCp);

	//BulletManager
	auto bulletManager = std::make_shared<BulletManagerCp>(pTank.get());
	pTank->AddComponent(bulletManager);

	//Points
	auto points = std::make_shared<PointsCp>(pTank.get(), 0);
	pTank->AddComponent(points);

	//Health
	auto health = std::make_shared<HealthCp>(pTank.get(), 3);
	pTank->AddComponent(health);

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
	constexpr float shootSpeed{ 300 };
	glm::vec2 shootUpSpeed = { 0.f, -shootSpeed };
	glm::vec2 shootDownSpeed = { 0.f, shootSpeed };
	glm::vec2 shootLeftSpeed = { -shootSpeed, 0.f};
	glm::vec2 shootRightSpeed = { shootSpeed, 0.f };

	auto* shootUp = new ShootCommand{ pTank.get(), shootUpSpeed };
	auto* shootDown = new ShootCommand{ pTank.get(), shootDownSpeed };
	auto* shootLeft = new ShootCommand{ pTank.get(), shootLeftSpeed };
	auto* shootRight = new ShootCommand{ pTank.get(), shootRightSpeed };

	InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_UP, shootUp);
	InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_DOWN, shootDown);
	InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_LEFT, shootLeft);
	InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_RIGHT, shootRight);
}

static void CreateTankController(Scene& scene)
{
	auto pTank = std::make_shared<dae::GameObject>();
	scene.Add(pTank);
	pTank->SetTag("RedPlayer");
	PlayerManager::GetInstance().AddPlayer(pTank);

	//Texture
	auto tankTxt = std::make_shared<dae::TextureComponent>(pTank.get());
	tankTxt->SetTexture("Resources/Sprites/RedTank.png");
	pTank->AddComponent(tankTxt);

	//BulletManager
	auto bulletManager = std::make_shared<BulletManagerCp>(pTank.get());
	pTank->AddComponent(bulletManager);


	//Collision
	auto collisionCp = std::make_shared<CollisionCp>(pTank.get());
	pTank->AddComponent(collisionCp);
	collisionCp->AddCollider(pTank.get());

	auto bulletCollisionCp = std::make_shared<BulletCollisionCp>(pTank.get());
	pTank->AddComponent(bulletCollisionCp);

	//Points
	auto points = std::make_shared<PointsCp>(pTank.get(), 0);
	pTank->AddComponent(points);

	//Health
	auto health = std::make_shared<HealthCp>(pTank.get(), 3);
	pTank->AddComponent(health);

	//Controller
	int controllerIdx{ 0 };
	dae::InputManager::GetInstance().AddController(controllerIdx);
	Controller::ControllerButton button{};


	//Movement
	constexpr float speed{ 1.5f };
	glm::vec3 up = { 0.f,-speed,0.f };
	glm::vec3 down = { 0.f,speed,0.f };
	glm::vec3 right = { speed,0.f,0.f };
	glm::vec3 left = { -speed,0.f,0.f };
	auto* moveCommandDownBlue = new MoveCommand{ pTank.get(), down };
	auto* moveCommandUpBlue = new MoveCommand{ pTank.get(), up };
	auto* moveCommandLeftBlue = new MoveCommand{ pTank.get(), left };
	auto* moveCommandRightBlue = new MoveCommand{ pTank.get(), right };

	button = Controller::ControllerButton::DpadDown;
	InputManager::GetInstance().BindControllerToCommand(controllerIdx, button, moveCommandDownBlue);
	button = Controller::ControllerButton::DpadUp;
	InputManager::GetInstance().BindControllerToCommand(controllerIdx, button, moveCommandUpBlue);
	button = Controller::ControllerButton::DpadLeft;
	InputManager::GetInstance().BindControllerToCommand(controllerIdx, button, moveCommandLeftBlue);
	button = Controller::ControllerButton::DpadRight;
	InputManager::GetInstance().BindControllerToCommand(controllerIdx, button, moveCommandRightBlue);


	//Shooting
	constexpr float shootSpeed{ 300 };
	glm::vec2 shootUpSpeed = { 0.f, -shootSpeed };
	glm::vec2 shootDownSpeed = { 0.f, shootSpeed};
	glm::vec2 shootLeftSpeed = { -shootSpeed, 0.f };
	glm::vec2 shootRightSpeed = { shootSpeed, 0.f };

	auto* shootUp = new ShootCommand{ pTank.get(), shootUpSpeed };
	auto* shootDown = new ShootCommand{ pTank.get(), shootDownSpeed };
	auto* shootLeft = new ShootCommand{ pTank.get(), shootLeftSpeed };
	auto* shootRight = new ShootCommand{ pTank.get(), shootRightSpeed };

	button = Controller::ControllerButton::ButtonY;
	InputManager::GetInstance().BindControllerToCommand(controllerIdx, button, shootUp);
	button = Controller::ControllerButton::ButtonA;
	InputManager::GetInstance().BindControllerToCommand(controllerIdx, button, shootDown);
	button = Controller::ControllerButton::ButtonX;
	InputManager::GetInstance().BindControllerToCommand(controllerIdx, button, shootLeft);
	button = Controller::ControllerButton::RightShoulder;
	InputManager::GetInstance().BindControllerToCommand(controllerIdx, button, shootRight);
}