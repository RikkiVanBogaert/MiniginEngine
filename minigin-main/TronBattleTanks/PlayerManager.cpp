#include "PlayerManager.h"

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

void PlayerManager::SpawnPlayers()
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
	auto pPointText = std::make_shared<UICp>(pPointObject.get(), font, "Points: ", SDL_Color{255, 0, 0, 255}, "Points");
	pPointObject->AddComponent(pPointText);
	//Player 2 UI
	auto pPointObject2 = std::make_shared<GameObject>();
	pPointObject2->SetTag("RedPlayer");
	pPointObject2->SetRelativePos({ 5, 300 });
	auto pPointText2 = std::make_shared<UICp>(pPointObject2.get(), font, "Points: ", SDL_Color{ 0, 0, 255, 255 }, "Points");
	pPointObject2->AddComponent(pPointText2);

	switch (GetInstance().GetGameMode())
	{
	case SinglePlayer:
		scene->Add(pPointObject);
		CreateEnemies(*scene, enemySpawn->GetPos());
		break;
	case Coop:
		amountPlayers = 2;
		scene->Add(pPointObject);
		scene->Add(pPointObject2);
		players[1]->SetTag("RedPlayer");
		players[1]->GetComponent<dae::TextureComponent>()->SetTexture("Resources/Sprites/RedTank.png");
		CreateEnemies(*scene, enemySpawn->GetPos());
		break;
	case Versus:
		amountPlayers = 2;
		scene->Add(pPointObject);
		pPointObject2->SetTag("BluePlayer");
		scene->Add(pPointObject2);
		players[1]->SetTag("BluePlayer");
		players[1]->GetComponent<dae::TextureComponent>()->SetTexture("Resources/Sprites/BlueTank.png");
		break;
	}

	for (int i{}; i < amountPlayers; ++i)
	{
		sceneManager.GetActiveScene()->Add(players[i]);
		players[i]->SetRelativePos(playerSpawn->GetPos()[i]);
	}
}