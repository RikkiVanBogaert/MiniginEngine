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
		const auto pMainObj = std::make_shared<GameObject>();
		scene.Add(pMainObj);

		auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
		auto smallFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 22);

		const auto gameOverObj = std::make_shared<GameObject>();
		const auto gameOverText = std::make_shared<TextComponent>(gameOverObj.get(), "GAME OVER", font, SDL_Color{ 255, 255, 255, 255 });
		gameOverObj->SetRelativePos({ 200, 40 });
		gameOverObj->AddComponent(gameOverText);
		pMainObj->AddChild(gameOverObj);

		//dont show this until name is entered
		const auto resetObj = std::make_shared<GameObject>("Explanation");
		const auto resetText = std::make_shared<TextComponent>(resetObj.get(), "Enter your name", smallFont, SDL_Color{ 255, 255, 255, 255 });
		resetObj->SetRelativePos({ 160, 100 });
		resetObj->AddComponent(resetText);
		pMainObj->AddChild(resetObj);

		const auto highObj = std::make_shared<GameObject>();
		const auto highText = std::make_shared<TextComponent>(highObj.get(), "HighScores: ", smallFont, SDL_Color{ 255, 255, 50, 255 });
		highObj->SetRelativePos({ 350, 145 });
		highObj->AddComponent(highText);
		pMainObj->AddChild(highObj);

		const auto pointsObj = std::make_shared<GameObject>();
		const auto pointsText = std::make_shared<TextComponent>(pointsObj.get(), "Points: ", smallFont, SDL_Color{ 255, 255, 255, 255 });
		pointsObj->SetRelativePos({ 10, 250 });
		pointsObj->AddComponent(pointsText);
		pMainObj->AddChild(pointsObj);


		const auto scoreObj = std::make_shared<GameObject>();
		scoreObj->SetTag("Score");
		int score{};
		for (const auto& p : PlayerManager::GetInstance().GetPlayers())
		{
			score += p->GetComponent<PointsCp>()->GetAmount();
		}
		const auto scoreText = std::make_shared<TextComponent>(scoreObj.get(), std::to_string(score), smallFont, SDL_Color{ 255, 255, 255, 255 });
		scoreObj->SetRelativePos({ 90, 250 });
		scoreObj->AddComponent(scoreText);
		pMainObj->AddChild(scoreObj);


		const auto pNameObj = std::make_shared<GameObject>();
		const auto pNameTest = std::make_shared<HighScoresCp>(pNameObj.get(), "temp", smallFont, SDL_Color{ 255, 0, 0, 255 });
		pNameObj->AddComponent(pNameTest);
		pNameObj->SetRelativePos({ 160, 250 });
		pMainObj->AddChild(pNameObj);


		//HighScores
		auto miniFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
		glm::vec2 pos{ 350, 190 };
		for (int i{}; i < 10; ++i)
		{
			const auto o = std::make_shared<GameObject>();
			const std::string text = " ";
			const auto t = std::make_shared<TextComponent>(o.get(), text, miniFont, SDL_Color{ 255, 255, 50, 255 });
			o->AddComponent(t);
			o->SetTag("HighScore" + std::to_string(i));
			o->SetRelativePos(pos);
			pMainObj->AddChild(o);
			pos.y += 25;
		}


	}
}