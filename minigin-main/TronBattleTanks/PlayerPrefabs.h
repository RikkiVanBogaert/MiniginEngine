#pragma once
#include <SDL_scancode.h>
#include <glm/vec3.hpp>

#include "BulletCollisionCp.h"
#include "BulletManagerCp.h"
#include "CollisionCp.h"
#include "DerCounterCps.h"
#include "GameCommands.h"
#include "InputManager.h"
#include "MoveCp.h"
#include "PlayerManager.h"
#include "Scene.h"
#include "TextureComponent.h"
#include "GunPrefab.h"

namespace dae
{

	static void CreateTankKeyboardAndController(Scene& scene)
	{
		auto pTank = std::make_shared<GameObject>();
		scene.Add(pTank);
		pTank->SetTag("RedPlayer");
		PlayerManager::GetInstance().AddPlayer(pTank);

		//Texture
		auto tankTxt = std::make_shared<TextureComponent>(pTank.get());
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
		auto health = std::make_shared<LivesCp>(pTank.get(), 3);
		pTank->AddComponent(health);


		//Movement
		auto moveCp = std::make_shared<MoveCp>(pTank.get(), 50.f);
		pTank->AddComponent(moveCp);

		constexpr float speed{ 1.5f };
		glm::vec3 up = { 0.f,-speed,0.f };
		glm::vec3 down = { 0.f,speed,0.f };
		glm::vec3 right = { speed,0.f,0.f };
		glm::vec3 left = { -speed,0.f,0.f };

		auto moveCommandUp = std::make_shared<MoveCommand>( pTank.get(), up);
		auto moveCommandDown = std::make_shared<MoveCommand>(pTank.get(), down);
		auto moveCommandLeft = std::make_shared<MoveCommand>(pTank.get(), left);
		auto moveCommandRight = std::make_shared<MoveCommand>(pTank.get(), right);

		InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_W, moveCommandUp);
		InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_S, moveCommandDown);
		InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_A, moveCommandLeft);
		InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_D, moveCommandRight);

		//Controller
		int controllerIdx{ PlayerManager::GetInstance().GetControllerIdx() };
		dae::InputManager::GetInstance().AddController(controllerIdx);
		++PlayerManager::GetInstance().GetControllerIdx();
		Controller::ControllerButton button{};

		button = Controller::ControllerButton::DpadDown;
		InputManager::GetInstance().BindControllerToCommand(controllerIdx, button, moveCommandDown);
		button = Controller::ControllerButton::DpadUp;
		InputManager::GetInstance().BindControllerToCommand(controllerIdx, button, moveCommandUp);
		button = Controller::ControllerButton::DpadLeft;
		InputManager::GetInstance().BindControllerToCommand(controllerIdx, button, moveCommandLeft);
		button = Controller::ControllerButton::DpadRight;
		InputManager::GetInstance().BindControllerToCommand(controllerIdx, button, moveCommandRight);

		//Shooting
		constexpr float shootSpeed{ 300 };
		glm::vec2 shootUpVel = { 0.f, -shootSpeed };
		glm::vec2 shootDownVel = { 0.f, shootSpeed };
		glm::vec2 shootLeftVel = { -shootSpeed, 0.f };
		glm::vec2 shootRightVel = { shootSpeed, 0.f };

		auto shootUp = std::make_shared<ShootCommand>(pTank.get(), shootUpVel);
		auto shootDown = std::make_shared<ShootCommand>(pTank.get(), shootDownVel);
		auto shootLeft = std::make_shared<ShootCommand>(pTank.get(), shootLeftVel);
		auto shootRight = std::make_shared<ShootCommand>(pTank.get(), shootRightVel);

		InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_UP, shootUp);
		InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_DOWN, shootDown);
		InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_LEFT, shootLeft);
		InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_RIGHT, shootRight);

		button = Controller::ControllerButton::ButtonY;
		InputManager::GetInstance().BindControllerToCommand(controllerIdx, button, shootUp);
		button = Controller::ControllerButton::ButtonA;
		InputManager::GetInstance().BindControllerToCommand(controllerIdx, button, shootDown);
		button = Controller::ControllerButton::ButtonX;
		InputManager::GetInstance().BindControllerToCommand(controllerIdx, button, shootLeft);
		button = Controller::ControllerButton::ButtonB;
		InputManager::GetInstance().BindControllerToCommand(controllerIdx, button, shootRight);

		pTank->AddChild(CreateTankGun(scene));
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
		auto health = std::make_shared<LivesCp>(pTank.get(), 3);
		pTank->AddComponent(health);

		//Controller
		int controllerIdx{ PlayerManager::GetInstance().GetControllerIdx() };
		dae::InputManager::GetInstance().AddController(controllerIdx);
		++PlayerManager::GetInstance().GetControllerIdx();
		Controller::ControllerButton button{};


		//Movement
		auto moveCp = std::make_shared<MoveCp>(pTank.get(), 50.f);
		pTank->AddComponent(moveCp);

		constexpr float speed{ 1.5f };
		glm::vec3 up = { 0.f,-speed,0.f };
		glm::vec3 down = { 0.f,speed,0.f };
		glm::vec3 right = { speed,0.f,0.f };
		glm::vec3 left = { -speed,0.f,0.f };

		auto moveCommandUp = std::make_shared<MoveCommand>(pTank.get(), up);
		auto moveCommandDown = std::make_shared<MoveCommand>(pTank.get(), down);
		auto moveCommandLeft = std::make_shared<MoveCommand>(pTank.get(), left);
		auto moveCommandRight = std::make_shared<MoveCommand>(pTank.get(), right);

		button = Controller::ControllerButton::DpadDown;
		InputManager::GetInstance().BindControllerToCommand(controllerIdx, button, moveCommandDown);
		button = Controller::ControllerButton::DpadUp;
		InputManager::GetInstance().BindControllerToCommand(controllerIdx, button, moveCommandUp);
		button = Controller::ControllerButton::DpadLeft;
		InputManager::GetInstance().BindControllerToCommand(controllerIdx, button, moveCommandLeft);
		button = Controller::ControllerButton::DpadRight;
		InputManager::GetInstance().BindControllerToCommand(controllerIdx, button, moveCommandRight);


		//Shooting
		constexpr float shootSpeed{ 300 };
		glm::vec2 shootUpVel = { 0.f, -shootSpeed };
		glm::vec2 shootDownVel = { 0.f, shootSpeed };
		glm::vec2 shootLeftVel = { -shootSpeed, 0.f };
		glm::vec2 shootRightVel = { shootSpeed, 0.f };

		auto shootUp = std::make_shared<ShootCommand>(pTank.get(), shootUpVel);
		auto shootDown = std::make_shared<ShootCommand>(pTank.get(), shootDownVel);
		auto shootLeft = std::make_shared<ShootCommand>(pTank.get(), shootLeftVel);
		auto shootRight = std::make_shared<ShootCommand>(pTank.get(), shootRightVel);

		button = Controller::ControllerButton::ButtonY;
		InputManager::GetInstance().BindControllerToCommand(controllerIdx, button, shootUp);
		button = Controller::ControllerButton::ButtonA;
		InputManager::GetInstance().BindControllerToCommand(controllerIdx, button, shootDown);
		button = Controller::ControllerButton::ButtonX;
		InputManager::GetInstance().BindControllerToCommand(controllerIdx, button, shootLeft);
		button = Controller::ControllerButton::ButtonB;
		InputManager::GetInstance().BindControllerToCommand(controllerIdx, button, shootRight);
	}
}