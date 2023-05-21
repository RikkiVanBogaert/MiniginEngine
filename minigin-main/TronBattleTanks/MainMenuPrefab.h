#pragma once
#include <SDL_pixels.h>
#include <SDL_scancode.h>

#include "GameCommands.h"
#include "InputManager.h"
#include "NameCp.h"
#include "ResourceManager.h"
#include "Scene.h"

using namespace dae;

static void CreateMainMenu(Scene& scene)
{
	auto pMenuObj = std::make_shared<GameObject>();
	scene.Add(pMenuObj);

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
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

	//GameMode
	{
		const auto switchGameModeObj = std::make_shared<GameObject>();
		const auto switchGameModeText = std::make_shared<TextComponent>(switchGameModeObj.get(), "Switch GameMode (Shift)", font, SDL_Color{ 255, 255, 255 });
		switchGameModeObj->SetRelativePos({ 150, 280 });
		switchGameModeObj->AddComponent(switchGameModeText);
		pMenuObj->AddChild(switchGameModeObj);

		const auto m_pGameModeObject = std::make_shared<GameObject>();
		m_pGameModeObject->SetTag("GameMode");
		auto m_pGameModeText = std::make_shared<TextComponent>(m_pGameModeObject.get(), "SinglePlayer", smallFont, SDL_Color{ 255, 255, 255 });
		m_pGameModeObject->SetRelativePos({ 200, 320 });
		m_pGameModeObject->AddComponent(m_pGameModeText);
		pMenuObj->AddChild(m_pGameModeObject);
	}

	//Input
	{
		const auto switchInputObj = std::make_shared<GameObject>();
		const auto switchInputText = std::make_shared<TextComponent>(switchInputObj.get(), "Switch Input (I)", font, SDL_Color{ 255, 255, 255 });
		switchInputObj->SetRelativePos({ 150, 350 });
		switchInputObj->AddComponent(switchInputText);
		pMenuObj->AddChild(switchInputObj);

		const auto inputObj = std::make_shared<GameObject>();
		inputObj->SetTag("Input");
		auto inputText = std::make_shared<TextComponent>(inputObj.get(), "Keyboard", smallFont, SDL_Color{ 255, 255, 255 });
		inputObj->SetRelativePos({ 200, 390 });
		inputObj->AddComponent(inputText);
		pMenuObj->AddChild(inputObj);
	}

	/*const auto nextLevelObj = std::make_shared<GameObject>();
	const auto nextLevelText = std::make_shared<TextComponent>(nextLevelObj.get(), "Next Level (N)", smallFont, SDL_Color{ 255, 255, 255 });
	nextLevelObj->SetRelativePos({ 10, 430 });
	nextLevelObj->AddComponent(nextLevelText);
	pMenuObj->AddChild(nextLevelObj);*/

	//INPUT
	auto* skipLevel = new SkipLevelCommand{};
	InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_N, skipLevel);

	auto* startGame = new StartGameCommand{};
	dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_SPACE, startGame);

	auto* exitGame = new ExitGameCommand{};
	dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_ESCAPE, exitGame);

	auto* switchGameMode = new SwitchGameModeCommand{};
	dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_TAB, switchGameMode);
}
