#include "PlayerManager.h"

#include "EnemyPrefab.h"
#include "SceneManager.h"
#include "SpawnPositionCp.h"
#include "Scene.h"
#include "GameObject.h"
#include "LevelPrefab.h"
#include "TextureComponent.h"


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
	PlayerSpawnPosCp* playerSpawn{};
	EnemySpawnPosCp* enemySpawn{};
	for (auto& o : sceneObjects)
	{
		if (o->GetTag() != "Level") continue;

		playerSpawn = o->GetComponent<PlayerSpawnPosCp>();
		enemySpawn = o->GetComponent<EnemySpawnPosCp>();
		break;
	}

	auto players = GetInstance().GetPlayers();

	int amountPlayers{ 1 };
	switch (GetInstance().GetGameMode())
	{
	case SinglePlayer:
		CreateEnemies(*SceneManager::GetInstance().GetActiveScene(), enemySpawn->GetPos());
		break;
	case Coop:
		amountPlayers = 2;

		players[1]->SetTag("Red");
		players[1]->GetComponent<dae::TextureComponent>()->SetTexture("Resources/Sprites/RedTank.png");
		CreateEnemies(*SceneManager::GetInstance().GetActiveScene(), enemySpawn->GetPos());
		break;
	case Versus:
		amountPlayers = 2;
		players[1]->SetTag("Blue");
		players[1]->GetComponent<dae::TextureComponent>()->SetTexture("Resources/Sprites/BlueTank.png");
		break;
	}

	for (int i{}; i < amountPlayers; ++i)
	{
		sceneManager.GetActiveScene()->Add(players[i]);
		players[i]->SetRelativePos(playerSpawn->GetPos()[i]);
	}
}