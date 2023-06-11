#include "GameManager.h"

#include "DerCounterCps.h"
#include "EnemyPrefab.h"
#include "GameHelpers.h"
#include "SceneManager.h"
#include "SpawnPositionCp.h"
#include "Scene.h"
#include "GameObject.h"
#include "LevelPrefab.h"
#include "Subject.h"
#include "TextureComponent.h"
#include "UICp.h"

using namespace dae;

void GameManager::SwitchGameMode()
{
	switch (m_GameMode)
	{
	case SinglePlayer:
		m_GameMode = Coop;
		break;
	case Coop:
		m_GameMode = Versus;
		break;
	case Versus:
		m_GameMode = SinglePlayer;
		break;
	}
}

void GameManager::LevelCreate()
{
	auto& sceneManager = SceneManager::GetInstance();

	const std::string filePath = "../Data/Resources/" + sceneManager.GetActiveSceneName() + ".csv";

	const auto pLevel = CreateLevel(*sceneManager.GetActiveScene(), filePath);
		
	const auto playerSpawn = pLevel->GetComponent<PlayerSpawnPosCp>();
	const auto blueEnemySpawn = pLevel->GetComponent<BlueEnemySpawnPosCp>();
	const auto recognizerSpawn = pLevel->GetComponent<RecognizerSpawnPosCp>();

	const auto players = GetInstance().GetPlayers();
	const auto scene = SceneManager::GetInstance().GetActiveScene();

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);

	const auto pPointObject = std::make_shared<GameObject>();
	pPointObject->SetRelativePos({5, 200});

	//Player 1 Lives
	const auto pLivesObject = std::make_shared<GameObject>();
	pLivesObject->SetRelativePos({ 5, 250 });

	//Player 2 Lives
	const auto pLivesObject2 = std::make_shared<GameObject>();
	pLivesObject2->SetRelativePos({ 5, 300 });

	switch (GetInstance().GetGameMode())
	{
	case SinglePlayer:
	{
		scene->Add(pPointObject);
		scene->Add(pLivesObject);
		CreateBlueEnemies(*scene, blueEnemySpawn->GetPos());
		CreateRecognizers(*scene, recognizerSpawn->GetPos());

		sceneManager.GetActiveScene()->Add(players[0]);
		players[0]->SetRelativePos(playerSpawn->GetPos()[0]);
	}
		break;
	case Coop:
	{
		scene->Add(pPointObject);
		scene->Add(pLivesObject);

		scene->Add(pLivesObject2);
		players[1]->SetTagIncludingChildren("RedPlayer");
		players[1]->GetComponent<TextureComponent>()->SetTexture("Resources/Sprites/GreenTank.png");
		CreateBlueEnemies(*scene, blueEnemySpawn->GetPos());
		CreateRecognizers(*scene, recognizerSpawn->GetPos());

		
		for(int i{}; i < players.size(); ++i)
		{
			sceneManager.GetActiveScene()->Add(players[i]);
			players[i]->SetRelativePos(playerSpawn->GetPos()[i]);
		}

		break;
	}
	case Versus:
	{
		scene->Add(pPointObject);
		scene->Add(pLivesObject);

		scene->Add(pLivesObject2);
		players[1]->SetTagIncludingChildren("BluePlayer");
		players[1]->GetComponent<TextureComponent>()->SetTexture("Resources/Sprites/BlueTank.png");

		CreateBlueEnemies(*scene, blueEnemySpawn->GetPos());
		CreateRecognizers(*scene, recognizerSpawn->GetPos());

		for (int i{}; i < players.size(); ++i)
		{
			sceneManager.GetActiveScene()->Add(players[i]);
			players[i]->SetRelativePos(playerSpawn->GetPos()[i]);
		}
		break;
	}
	}


	const auto pPointText = std::make_shared<UIPointsCp>(pPointObject.get(), "Points: ", font,
		SDL_Color{ 255, 255, 255, 255 }, GetPlayers()[0]->GetComponent<PointsCp>());
	pPointObject->AddComponent(pPointText);

	const auto pLivesText = std::make_shared<UILivesCp>(pLivesObject.get(), "Lives: ", font,
		SDL_Color{ 255, 0, 0, 255 }, GetPlayers()[0]->GetComponent<LivesCp>());
	pLivesObject->AddComponent(pLivesText);

	const auto pLivesText2 = std::make_shared<UILivesCp>(pLivesObject2.get(), "Lives: ", font,
		SDL_Color{ 255, 255, 0, 255 }, GetPlayers()[1]->GetComponent<LivesCp>());
	pLivesObject2->AddComponent(pLivesText2);


}

void GameManager::ResetPlayerVars()
{
	for(auto p : GetPlayers())
	{
		p->GetComponent<PointsCp>()->SetAmount(0);
		p->GetComponent<LivesCp>()->SetAmount(3);
	}
}

void GameManager::RemovePlayerFromScene(GameObject* player) const
{
	for(const auto& p : m_Players)
	{
		if(p.get() == player)
		{
			p->GetScene()->Remove(p);
		}
	}
}

void GameManager::RemoveAllPlayersFromScene()
{
	for(const auto& p : GetPlayers())
	{
		p->GetScene()->Remove(p);
	}
}

void GameManager::ResetScene()
{
	SceneManager::GetInstance().GetActiveScene()->RemoveAll();
	LevelCreate();
}

void GameManager::NextLevel()
{
	auto& sceneManager = SceneManager::GetInstance();
	const auto oldScene = sceneManager.GetActiveScene();
	RemoveAllPlayersFromScene();
	for(auto g : oldScene->GetGameObjects())
	{
		g->MarkForDeletion();
	}
	sceneManager.NextScene();
	SkipNonLevels();

	LevelCreate();


}

void GameManager::SkipNonLevels() const
{
	const auto sceneName = SceneManager::GetInstance().GetActiveScene()->GetName();
	if (sceneName == "WaitingScene" || sceneName == "MainMenu" || sceneName == "GameOver")
	{
		SceneManager::GetInstance().NextScene();
		SkipNonLevels();
	}
}
