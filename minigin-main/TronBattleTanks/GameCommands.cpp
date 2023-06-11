#include "GameCommands.h"

#include "AudioService.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "GameManager.h"

#include "Scene.h"
#include "BulletManagerCp.h"
#include "CollisionCp.h"
#include "GameHelpers.h"
#include "HighScoresCp.h"
#include "MoveCp.h"
#include "TextComponent.h"
#include "InputManager.h" //putting this include higher causes Uint8 undeclared errors
#include "PlayerManager.h"


using namespace dae;

MoveCommand::MoveCommand(GameObject* gameObj, const glm::vec2& direction, int controllerIdx,
	Controller::ControllerStick stick):
	m_pGameObject(gameObj),
	m_Direction(direction),
	m_ControllerIdx(controllerIdx),
	m_ControllerStick(stick)
{}

void MoveCommand::Execute(bool useStickDir)
{
	if (!m_pGameObject || m_pGameObject->NeedsDeleting() || !m_pGameObject->GetScene()->IsActive()) return;

	//Collision
	auto moveDir = m_Direction;

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
		if (collisionCp && collisionCp->CollisionHit(m_pGameObject, moveDir))
		{
			return;
		}
	}

	const auto moveCp = m_pGameObject->GetComponent<MoveCp>();
	moveCp->Move(moveDir);
}

bool MoveCommand::CheckAllMoveDirections(glm::vec2& moveDir) const
{
	const auto collisionCp = GetComponentInScene<CollisionCp>(m_pGameObject->GetScene(), "Level");

	if (!collisionCp) return true; /// collisionCp so move freely

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
m_pGameObject(gameObj),
m_Direction(direction),
m_ControllerIdx(controllerIdx),
m_ControllerStick(stick)
{}

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
	if (sceneManager.GetActiveSceneName() == "MainMenu" || 
		sceneManager.GetActiveSceneName() == "GameOver")
	{
		SetKeyPressed(true);
		return;
	}

	GameManager::GetInstance().NextLevel();
	
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
	GameManager::GetInstance().LevelCreate();

	SetKeyPressed(true);
}


void SwitchGameModeCommand::Execute(bool)
{
	if (GetKeyPressed()) return;

	if (SceneManager::GetInstance().GetActiveSceneName() != "MainMenu")
	{
		SetKeyPressed(true);
		return;
	}

	GameManager::GetInstance().SwitchGameMode();

	const auto gameModeObject = GetGameObject(SceneManager::GetInstance().GetActiveScene(), "GameMode");
	const auto gameModeText = gameModeObject->GetComponent<TextComponent>();

	switch (GameManager::GetInstance().GetGameMode())
	{
	case GameManager::SinglePlayer:
		gameModeText->SetText("SinglePlayer");
		break;
	case GameManager::Coop:
		gameModeText->SetText("Coop");
		break;
	case GameManager::Versus:
		gameModeText->SetText("Versus");
		break;
	}

	SetKeyPressed(true);
}


void ResetGameCommand::Execute(bool)
{
	if (GetKeyPressed()) return;

	if (SceneManager::GetInstance().GetActiveSceneName() != "GameOver")
		return;

	const auto highScoreCp = GetComponentInScene<HighScoresCp>(SceneManager::GetInstance().GetActiveScene());
	if(highScoreCp)
	{
		if(!highScoreCp->IsNameSet())
		{
			SetKeyPressed(true);
			return;
		}
	}
	else
	{
		SetKeyPressed(true);
		return;
	}
	
	auto& sceneManager = SceneManager::GetInstance();
	sceneManager.GetActiveScene()->RemoveAll();
	sceneManager.SetActiveScene("MainMenu");

	SetKeyPressed(true);
}

void MuteCommand::Execute(bool)
{
	if (GetKeyPressed()) return;

	auto& ss = ServiceLocator::GetSoundSystem(); 
	ss.MuteUnmuteSound();

	SetKeyPressed(true);
}
