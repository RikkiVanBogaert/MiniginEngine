#include "GameCommands.h"

#include "AudioService.h"
#include "GameObject.h"
#include "CounterCp.h"
#include "SceneManager.h"
#include "PlayerManager.h"

#include "Scene.h"
#include "BulletManagerCp.h"
#include "CollisionCp.h"
#include "DerCounterCps.h"
#include "GameHelpers.h"
#include "MoveCp.h"
#include "TextComponent.h"


using namespace dae;

MoveCommand::MoveCommand(GameObject* gameObj, const glm::vec3& direction)
{
	m_pGameObject = gameObj;
	m_Direction = direction;
}

void MoveCommand::Execute()
{
	if (!m_pGameObject || m_pGameObject->NeedsDeleting() || !m_pGameObject->GetScene()->IsActive()) return;

	//Collision
	const auto sceneObjects = m_pGameObject->GetScene()->GetGameObjects();
	for (auto& o : sceneObjects)
	{
		if (o->GetTag() != "Level") continue;

		const auto collisionCp = o->GetComponent<CollisionCp>();
		if (collisionCp->CollisionHit(m_pGameObject, m_Direction))
			return;
		
		break;
	}

	const auto moveCp = m_pGameObject->GetComponent<MoveCp>();
	moveCp->Move(m_Direction);
}

ShootCommand::ShootCommand(dae::GameObject* gameObj, const glm::vec2& direction)
{
	m_pGameObject = gameObj;
	m_Direction = direction;
}

void ShootCommand::Execute()
{
	if (!m_pGameObject || m_pGameObject->NeedsDeleting() || !m_pGameObject->GetScene()->IsActive()) return;

	if (GetKeyPressed()) return;

	const auto bulletManager = m_pGameObject->GetComponent<BulletManagerCp>();
	bulletManager->Shoot(m_Direction);

	SetKeyPressed(true);
}

void SkipLevelCommand::Execute()
{
	if (GetKeyPressed()) return;

	const auto& sceneManager = SceneManager::GetInstance();
	if (sceneManager.GetActiveSceneName() == "MainMenu")
	{
		SetKeyPressed(true);
		return;
	}

	PlayerManager::GetInstance().NextLevel();
	
	SetKeyPressed(true);
}

void StartGameCommand::Execute()
{
	if (GetKeyPressed()) return;

	if (SceneManager::GetInstance().GetActiveSceneName() != "MainMenu")
	{
		SetKeyPressed(true);
		return;
	}

	const std::string nameScene{"Level0"};
	auto& sceneManager = SceneManager::GetInstance();
	sceneManager.SetActiveScene(nameScene);

	PlayerManager::GetInstance().ResetPlayerVars();
	PlayerManager::GetInstance().LevelCreate();

	SetKeyPressed(true);
}


void ExitGameCommand::Execute()
{
	exit(0);
}

void SwitchGameModeCommand::Execute()
{
	if (GetKeyPressed()) return;
	if (SceneManager::GetInstance().GetActiveSceneName() != "MainMenu")
	{
		SetKeyPressed(true);
		return;
	}

	PlayerManager::GetInstance().SwitchGameMode();

	const auto gameModeObject = GetGameObject(SceneManager::GetInstance().GetActiveScene(), "GameMode");
	const auto gameModeText = gameModeObject->GetComponent<TextComponent>();

	switch (PlayerManager::GetInstance().GetGameMode())
	{
	case PlayerManager::SinglePlayer:
		gameModeText->SetText("SinglePlayer");
		break;
	case PlayerManager::Coop:
		gameModeText->SetText("Coop");
		break;
	case PlayerManager::Versus:
		gameModeText->SetText("Versus");
		break;
	}

	SetKeyPressed(true);
}


void ResetGameCommand::Execute()
{
	if (GetKeyPressed()) return;

	if (SceneManager::GetInstance().GetActiveSceneName() == "MainMenu")
		return;
	
	auto& sceneManager = SceneManager::GetInstance();
	sceneManager.GetActiveScene()->RemoveAll();
	sceneManager.SetActiveScene("MainMenu");
	SetKeyPressed(true);
	
}

void MuteCommand::Execute()
{
	auto& ss = ServiceLocator::GetSoundSystem(); 
	ss.MuteUnmuteSound();
}
