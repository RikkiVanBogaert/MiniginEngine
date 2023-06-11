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
#include "GameManager.h"
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
		GameManager::GetInstance().AddPlayer(pTank);

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


		//Points
		auto points = std::make_shared<PointsCp>(pTank.get(), 0);
		pTank->AddComponent(points);

		//Health
		auto health = std::make_shared<LivesCp>(pTank.get(), 3);
		pTank->AddComponent(health);


		//Create Controller
		int controllerIdx{ GameManager::GetInstance().GetControllerIdx() };
		InputManager::GetInstance().AddController(controllerIdx);
		++GameManager::GetInstance().GetControllerIdx();

		//Movement
		auto moveCp = std::make_shared<MoveCp>(pTank.get(), 65.f);
		pTank->AddComponent(moveCp);

		constexpr float speed{ 1.5f };
		glm::vec3 up = { 0.f,-speed,0.f };
		glm::vec3 down = { 0.f,speed,0.f };
		glm::vec3 right = { speed,0.f,0.f };
		glm::vec3 left = { -speed,0.f,0.f };

		auto moveCommandUp = std::make_shared<MoveCommand>( pTank.get(), up);
		auto moveCommandDown = std::make_shared<MoveCommand>(pTank.get(), down);
		auto moveCommandLeft = std::make_shared<MoveCommand>(pTank.get(), left);
		auto moveCommandRight = std::make_shared<MoveCommand>(pTank.get(), right, controllerIdx);

		InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_W, moveCommandUp);
		InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_S, moveCommandDown);
		InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_A, moveCommandLeft);
		InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_D, moveCommandRight);

		Controller::ControllerStick t = Controller::ControllerStick::LeftStick;
		InputManager::GetInstance().BindControllerToCommand(controllerIdx, t, moveCommandRight);


		//Gun-Shooting
		const auto pGun = CreateTankGun(scene, controllerIdx);
		pGun->SetTag(pTank->GetTag());
		pTank->AddChild(pGun);
	}

	static void CreateTankController(Scene& scene)
	{
		const auto pTank = std::make_shared<GameObject>();
		scene.Add(pTank);
		pTank->SetTag("RedPlayer");
		GameManager::GetInstance().AddPlayer(pTank);

		//Texture
		const auto tankTxt = std::make_shared<TextureComponent>(pTank.get());
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
		const auto health = std::make_shared<LivesCp>(pTank.get(), 3);
		pTank->AddComponent(health);


		//Create Controller
		int controllerIdx{ GameManager::GetInstance().GetControllerIdx() };
		InputManager::GetInstance().AddController(controllerIdx);
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

		Controller::ControllerStick t = Controller::ControllerStick::LeftStick;
		InputManager::GetInstance().BindControllerToCommand(controllerIdx, t, moveCommandRight);


		//Gun-Shooting
		const auto pGun = CreateTankGun(scene, controllerIdx, false);
		pGun->SetTag(pTank->GetTag());
		pTank->AddChild(pGun);
	}
}