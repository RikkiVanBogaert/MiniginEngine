#pragma once
#include "GameObject.h"
#include "Scene.h"
#include "TextureComponent.h"


static std::shared_ptr<dae::GameObject> CreateTankGun(dae::Scene& scene, int controllerIdx, bool usingKeyboard = true)
{
	auto pGun = std::make_shared<dae::GameObject>();
	scene.Add(pGun);

	pGun->SetRelativePos({ -11, -8 });

	//Texture
	const auto gunTxt = std::make_shared<dae::TextureComponent>(pGun.get());
	gunTxt->SetTexture("Resources/Sprites/RedTankGun.png");
	pGun->AddComponent(gunTxt);

	//BulletManager
	const auto bulletManager = std::make_shared<BulletManagerCp>(pGun.get());
	pGun->AddComponent(bulletManager);

	//Shooting
	glm::vec2 shootUpVel = { 0.f, -1 };
	glm::vec2 shootDownVel = { 0.f, 1 };
	glm::vec2 shootLeftVel = { -1, 0.f };
	glm::vec2 shootRightVel = { 1, 0.f };

	const auto shootUp = std::make_shared<ShootCommand>(pGun.get(), shootUpVel);
	const auto shootDown = std::make_shared<ShootCommand>(pGun.get(), shootDownVel);
	const auto shootLeft = std::make_shared<ShootCommand>(pGun.get(), shootLeftVel);
	const auto shootRight = std::make_shared<ShootCommand>(pGun.get(), shootRightVel, controllerIdx);

	if (usingKeyboard)
	{
		dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_UP, shootUp);
		dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_DOWN, shootDown);
		dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_LEFT, shootLeft);
		dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_RIGHT, shootRight);
	}

	dae::Controller::ControllerStick t = dae::Controller::ControllerStick::RightStick;
	dae::InputManager::GetInstance().BindControllerToCommand(controllerIdx, t, shootRight);

	return pGun;
}
