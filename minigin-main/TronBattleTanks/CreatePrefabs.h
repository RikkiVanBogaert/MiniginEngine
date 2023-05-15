#pragma once
#include "GameObject.h"
#include "TextureComponent.h"

static std::shared_ptr<dae::GameObject> CreateTank()
{
	auto pTank = std::make_shared<dae::GameObject>();

	//Texture
	auto tankTxt = std::make_shared<dae::TextureComponent>(pTank.get());
	tankTxt->SetTexture("Resources/Sprites/RedTank.png");
	pTank->AddComponent(tankTxt);

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


	return pTank;
}
