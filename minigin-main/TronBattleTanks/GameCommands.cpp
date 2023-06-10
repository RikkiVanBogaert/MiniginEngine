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
#include "InputManager.h" //putting this include higher causes Uint8 undeclared errors


using namespace dae;

MoveCommand::MoveCommand(GameObject* gameObj, const glm::vec2& direction, int controllerIdx,
	Controller::ControllerStick stick):
	m_Direction(direction),
	m_ControllerIdx(controllerIdx),
	m_ControllerStick(stick)
{
	m_pGameObject = gameObj;
}

void MoveCommand::Execute(bool useStickDir)
{
	if (!m_pGameObject || m_pGameObject->NeedsDeleting() || !m_pGameObject->GetScene()->IsActive()) return;

	//Collision
	auto moveDir = m_Direction;

	const auto sceneObjects = m_pGameObject->GetScene()->GetGameObjects();
	if(useStickDir)
	{
		moveDir = InputManager::GetInstance().GetControllerStickValues(m_ControllerIdx, m_ControllerStick);
		if(!CheckAllMoveDirections(moveDir))
		{
			return;
		}
	}
	else
	{
		const auto collisionCp = GetComponentInScene<CollisionCp>(m_pGameObject->GetScene(), "Level");
		if (collisionCp->CollisionHit(m_pGameObject, moveDir))
		{
			return;
		}
	}

	const auto moveCp = m_pGameObject->GetComponent<MoveCp>();
	moveCp->Move(moveDir);
}

bool MoveCommand::CheckAllMoveDirections(glm::vec2& moveDir)
{
	const auto collisionCp = GetComponentInScene<CollisionCp>(m_pGameObject->GetScene(), "Level");

	if(abs(moveDir.x) > abs(moveDir.y))
	{
		if (!collisionCp->CollisionHit(m_pGameObject, { moveDir.x, 0 }))
		{
			moveDir.y = 0;
			return true;
		}

		if (moveDir.y != 0 &&
			!collisionCp->CollisionHit(m_pGameObject, { 0, moveDir.y }))
		{
			moveDir.x = 0;
			return true;
		}
	}
	else
	{
		if (!collisionCp->CollisionHit(m_pGameObject, { 0, moveDir.y }))
		{
			moveDir.x = 0;
			return true;
		}

		if (moveDir.x != 0 && 
			!collisionCp->CollisionHit(m_pGameObject, { moveDir.x, 0 }))
		{
			moveDir.y = 0;
			return true;
		}
	}

	return false;

}

ShootCommand::ShootCommand(dae::GameObject* gameObj, const glm::vec2& direction, int controllerIdx,
                           Controller::ControllerStick stick):
m_Direction(direction),
m_ControllerIdx(controllerIdx),
m_ControllerStick(stick)
{
	m_pGameObject = gameObj;
}

void ShootCommand::Execute(bool useStickDir)
{
	if (!m_pGameObject || m_pGameObject->NeedsDeleting() || !m_pGameObject->GetScene()->IsActive()) return;


	const auto bulletManager = m_pGameObject->GetComponent<BulletManagerCp>();

	auto shootDir = m_Direction;

	if(useStickDir)
	{
		shootDir = InputManager::GetInstance().GetControllerStickValues(m_ControllerIdx, m_ControllerStick);

		//to always shoot bullets straight
		if(abs(shootDir.x) >= abs(shootDir.y))
		{
			shootDir.y = 0;
		}
		else
		{
			shootDir.x = 0;
		}
	}

	bulletManager->Shoot(shootDir);
}

void SkipLevelCommand::Execute(bool)
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

void StartGameCommand::Execute(bool)
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


void ExitGameCommand::Execute(bool)
{
	exit(0);
}

void SwitchGameModeCommand::Execute(bool)
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


void ResetGameCommand::Execute(bool)
{
	if (GetKeyPressed()) return;

	if (SceneManager::GetInstance().GetActiveSceneName() == "MainMenu")
		return;
	
	auto& sceneManager = SceneManager::GetInstance();
	sceneManager.GetActiveScene()->RemoveAll();
	sceneManager.SetActiveScene("MainMenu");
	SetKeyPressed(true);
	
}

void MuteCommand::Execute(bool)
{
	auto& ss = ServiceLocator::GetSoundSystem(); 
	ss.MuteUnmuteSound();
}
