#pragma once
#include <SDL_pixels.h>
#include <SDL_scancode.h>

#include "GameCommands.h"
#include "InputManager.h"
#include "HighScoresCp.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "Scene.h"

static void CreateMainMenu(dae::Scene& scene)
{
	const auto pMenuObj = std::make_shared<dae::GameObject>();
	scene.Add(pMenuObj);

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 32);
	auto smallFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);

	const auto startObj = std::make_shared<dae::GameObject>();
	const auto startText = std::make_shared<dae::TextComponent>(startObj.get(), "START (Space/Button A)", font, SDL_Color{ 255, 255, 255, 255 });
	startObj->SetRelativePos({ 120, 170 });
	startObj->AddComponent(startText);
	pMenuObj->AddChild(startObj);

	//GameMode
	const auto switchGameModeObj = std::make_shared<dae::GameObject>();
	const auto switchGameModeText = std::make_shared<dae::TextComponent>(switchGameModeObj.get(), "Switch GameMode (Shift/Button X)", font, SDL_Color{ 255, 255, 255, 255 });
	switchGameModeObj->SetRelativePos({ 60, 240 });
	switchGameModeObj->AddComponent(switchGameModeText);
	pMenuObj->AddChild(switchGameModeObj);

	const auto m_pGameModeObject = std::make_shared<dae::GameObject>();
	m_pGameModeObject->SetTag("GameMode");
	const auto m_pGameModeText = std::make_shared<dae::TextComponent>(m_pGameModeObject.get(), "SinglePlayer", smallFont, SDL_Color{ 255, 255, 255, 255 });
	m_pGameModeObject->SetRelativePos({ 210, 280 });
	m_pGameModeObject->AddComponent(m_pGameModeText);
	pMenuObj->AddChild(m_pGameModeObject);

	const auto switchGameMode = std::make_shared<SwitchGameModeCommand>();
	dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_TAB, switchGameMode);

	const auto startGame = std::make_shared<StartGameCommand>();
	dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_SPACE, startGame);

	const int amountControllers = GameManager::GetInstance().GetControllerIdx();
	for (int i{}; i < amountControllers; ++i)
	{
		dae::Controller::ControllerButton button = dae::Controller::ControllerButton::ButtonA;
		dae::InputManager::GetInstance().BindControllerToCommand(i, button, startGame);

		button = dae::Controller::ControllerButton::ButtonX;
		dae::InputManager::GetInstance().BindControllerToCommand(i, button, switchGameMode);
	}
}