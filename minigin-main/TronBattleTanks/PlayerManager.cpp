#include "PlayerManager.h"

#include "DerCounterCps.h"
#include "EnemyPrefab.h"
#include "SceneManager.h"
#include "SpawnPositionCp.h"
#include "Scene.h"
#include "GameObject.h"
#include "LevelPrefab.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "UICp.h"


void PlayerManager::SwitchGameMode()
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

void PlayerManager::LevelCreate()
{
	auto& sceneManager = dae::SceneManager::GetInstance();

	const std::string filePath = "../Data/Resources/" + sceneManager.GetActiveSceneName() + ".csv";
	CreateLevel(*sceneManager.GetActiveScene(), filePath);


	const auto sceneObjects = sceneManager.GetActiveScene()->GetGameObjects();
	const PlayerSpawnPosCp* playerSpawn{};
	const EnemySpawnPosCp* enemySpawn{};
	for (auto& o : sceneObjects)
	{
		if (o->GetTag() != "Level") continue;

		playerSpawn = o->GetComponent<PlayerSpawnPosCp>();
		enemySpawn = o->GetComponent<EnemySpawnPosCp>();
		break;
	}

	const auto players = GetInstance().GetPlayers();
	auto scene = SceneManager::GetInstance().GetActiveScene();
	int amountPlayers{ 1 };

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
	//Player 1 UI
	auto pPointObject = std::make_shared<GameObject>();
	pPointObject->SetTag("RedPlayer");
	pPointObject->SetRelativePos({5, 200});

	auto pLivesObject = std::make_shared<GameObject>();
	pLivesObject->SetTag("RedPlayer");
	pLivesObject->SetRelativePos({ 5, 250 });

	//Player 2 UI
	auto pPointObject2 = std::make_shared<GameObject>();
	pPointObject2->SetTag("RedPlayer");
	pPointObject2->SetRelativePos({ 5, 300 });

	auto pLivesObject2 = std::make_shared<GameObject>();
	pLivesObject2->SetTag("RedPlayer");
	pLivesObject2->SetRelativePos({ 5, 350 });

	switch (GetInstance().GetGameMode())
	{
	case SinglePlayer:
		scene->Add(pPointObject);
		scene->Add(pLivesObject);
		CreateEnemies(*scene, enemySpawn->GetPos());
		break;
	case Coop:
		amountPlayers = 2;
		scene->Add(pPointObject);
		scene->Add(pLivesObject);

		scene->Add(pPointObject2);
		scene->Add(pLivesObject2);
		players[1]->SetTag("RedPlayer");
		players[1]->GetComponent<dae::TextureComponent>()->SetTexture("Resources/Sprites/GreenTank.png");
		CreateEnemies(*scene, enemySpawn->GetPos());
		break;
	case Versus:
		amountPlayers = 2;
		scene->Add(pPointObject);
		scene->Add(pLivesObject);

		scene->Add(pPointObject2);
		pPointObject2->SetTag("BluePlayer");
		scene->Add(pLivesObject2);
		pLivesObject2->SetTag("BluePlayer");
		players[1]->SetTag("BluePlayer");
		players[1]->GetComponent<dae::TextureComponent>()->SetTexture("Resources/Sprites/BlueTank.png");
		break;
	}

	for (int i{}; i < amountPlayers; ++i)
	{
		sceneManager.GetActiveScene()->Add(players[i]);
		players[i]->SetRelativePos(playerSpawn->GetPos()[i]);
	}

	const auto pPointText = std::make_shared<UIPointsCp>(pPointObject.get(), "Points: ", font,
		SDL_Color{ 255, 0, 0, 255 }, GetPlayers()[0]->GetComponent<PointsCp>());
	pPointObject->AddComponent(pPointText);

	const auto pPointText2 = std::make_shared<UIPointsCp>(pPointObject2.get(),"Points: ", font,
		SDL_Color{ 0, 0, 255, 255 }, GetPlayers()[1]->GetComponent<PointsCp>());
	pPointObject2->AddComponent(pPointText2);

	const auto pLivesText = std::make_shared<UILivesCp>(pLivesObject.get(), "Lives: ", font,
		SDL_Color{ 255, 0, 0, 255 }, GetPlayers()[0]->GetComponent<LivesCp>());
	pLivesObject->AddComponent(pLivesText);

	const auto pLivesText2 = std::make_shared<UILivesCp>(pLivesObject2.get(), "Lives: ", font,
		SDL_Color{ 0, 0, 255, 255 }, GetPlayers()[1]->GetComponent<LivesCp>());
	pLivesObject2->AddComponent(pLivesText2);


}

void PlayerManager::ResetPlayerVars()
{
	for(auto p : GetPlayers())
	{
		p->GetComponent<PointsCp>()->SetAmount(0);
		p->GetComponent<LivesCp>()->SetAmount(3);
	}
}

void PlayerManager::RemovePlayerFromScene(GameObject* player)
{
	for(auto p : m_Players)
	{
		if(p.get() == player)
		{
			p->GetScene()->Remove(p);
		}
	}
}

void PlayerManager::ResetScene()
{
	SceneManager::GetInstance().GetActiveScene()->RemoveAll();
	LevelCreate();
}

void PlayerManager::ReloadPlayers()
{

}
