#pragma once
#include <SDL_pixels.h>

#include "GameCommands.h"
#include "InputManager.h"
#include "HighScoresCp.h"
#include "PlayerManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "UICp.h"

namespace dae
{

	static void CreateGameOver(Scene& scene)
	{
		auto pMainObj = std::make_shared<GameObject>();
		pMainObj->SetTag("Main");
		scene.Add(pMainObj);

		auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
		auto smallFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 22);

		const auto gameOverObj = std::make_shared<GameObject>();
		const auto gameOverText = std::make_shared<TextComponent>(gameOverObj.get(), "GAME OVER", font, SDL_Color{ 255, 255, 255 });
		gameOverObj->SetRelativePos({ 200, 40 });
		gameOverObj->AddComponent(gameOverText);
		pMainObj->AddChild(gameOverObj);

		const auto resetObj = std::make_shared<GameObject>();
		const auto resetText = std::make_shared<TextComponent>(resetObj.get(), "Reset Game (R)", smallFont, SDL_Color{ 255, 255, 255 });
		resetObj->SetRelativePos({ 220, 100 });
		resetObj->AddComponent(resetText);
		pMainObj->AddChild(resetObj);

		const auto highObj = std::make_shared<GameObject>();
		const auto highText = std::make_shared<TextComponent>(highObj.get(), "HighScores: ", smallFont, SDL_Color{ 255, 255, 50 });
		highObj->SetRelativePos({ 350, 145 });
		highObj->AddComponent(highText);
		pMainObj->AddChild(highObj);

		const auto pointsObj = std::make_shared<GameObject>();
		const auto pointsText = std::make_shared<TextComponent>(pointsObj.get(), "Points: ", smallFont, SDL_Color{ 255, 255, 255 });
		pointsObj->SetRelativePos({ 10, 250 });
		pointsObj->AddComponent(pointsText);
		pMainObj->AddChild(pointsObj);


		const auto scoreObj = std::make_shared<GameObject>();
		scoreObj->SetTag("Score");
		int score{};
		for (const auto p : PlayerManager::GetInstance().GetPlayers())
		{
			score += p->GetComponent<PointsCp>()->GetAmount();
		}
		const auto scoreText = std::make_shared<TextComponent>(scoreObj.get(), std::to_string(score), smallFont, SDL_Color{ 255, 255, 255 });
		scoreObj->SetRelativePos({ 90, 250 });
		scoreObj->AddComponent(scoreText);
		pMainObj->AddChild(scoreObj);


		const auto pNameObj = std::make_shared<GameObject>();
		const auto pNameTest = std::make_shared<HighScoresCp>(pNameObj.get(), "temp", smallFont, SDL_Color{ 255, 0, 0, 255 });
		pNameObj->AddComponent(pNameTest);
		pNameObj->SetRelativePos({ 160, 250 });
		pMainObj->AddChild(pNameObj);


	}
}