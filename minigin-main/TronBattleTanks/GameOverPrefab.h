#pragma once
#include <SDL_pixels.h>

#include "GameCommands.h"
#include "InputManager.h"
#include "NameCp.h"
#include "PlayerManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "UICp.h"

using namespace dae;

static void CreateGameOver(Scene& scene)
{
	auto pMainObj = std::make_shared<GameObject>();
	scene.Add(pMainObj);

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto smallFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 22);

	const auto gameOverObj = std::make_shared<GameObject>();
	const auto gameOverText = std::make_shared<TextComponent>(gameOverObj.get(), "GAME OVER", font, SDL_Color{ 255, 255, 255 });
	gameOverObj->SetRelativePos({ 200, 40 });
	gameOverObj->AddComponent(gameOverText);
	pMainObj->AddChild(gameOverObj);

	const auto scoreP1 = std::make_shared<GameObject>();
	scoreP1->SetTag("P1Points");
	auto pointCp = PlayerManager::GetInstance().GetPlayers()[0]->GetComponent<PointsCp>();
	const auto scoreP1Text = std::make_shared<UIPointsCp>(scoreP1.get(), "Player 1: ", smallFont, SDL_Color{255, 0, 0}, pointCp);
	scoreP1->SetRelativePos({ 10, 250 });
	scoreP1->AddComponent(scoreP1Text);
	pMainObj->AddChild(scoreP1);

	const auto pNameObj = std::make_shared<GameObject>();
	const auto pNameTest = std::make_shared<NameCp>(pNameObj.get(), "temp", smallFont, SDL_Color{ 255, 0, 0, 255 });
	pNameObj->AddComponent(pNameTest);
	pNameObj->SetRelativePos({ 140, 250 });
	pMainObj->AddChild(pNameObj);


}
