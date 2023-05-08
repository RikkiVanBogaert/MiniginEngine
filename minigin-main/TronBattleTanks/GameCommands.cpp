#include "GameCommands.h"
#include "GameObject.h"
#include "CounterCp.h"
#include "SceneManager.h"
#include "PlayerManager.h"

#include "Scene.h"
#include "Level.h"
#include "Menu.h"
#include "Bullet.h"


using namespace dae;

MoveCommand::MoveCommand(GameObject* gameObj, const glm::vec3& direction)
{
	m_pGameObject = gameObj;
	m_Direction = direction;
}

void MoveCommand::Execute()
{
	if (!m_pGameObject || m_pGameObject->NeedsDeleting() || !m_pGameObject->GetScene()->IsActive()) return;

	//Rotate


	//Check level for collision
	const auto sceneObjects = m_pGameObject->GetScene()->GetGameObjects();
	for (auto& o : sceneObjects)
	{
		if (!dynamic_cast<Level*>(o.get())) continue;

		const auto pLevel = dynamic_cast<Level*>(o.get());
		if (pLevel->CollisionHit(m_pGameObject, m_Direction))
			return;
		else
			break;
	}

	//Movement
	glm::vec2 pos = m_pGameObject->GetRelativeTransform();
	pos.x += m_Direction.x;
	pos.y += m_Direction.y;

	m_pGameObject->SetRelativePos(pos);
}

DieCommand::DieCommand(GameObject* gameObj)
{
	m_pGameObject = gameObj;
}

void DieCommand::Execute()
{
	if (!m_pGameObject || m_pGameObject->NeedsDeleting() || !m_pGameObject->GetScene()->IsActive()) return;

	if (const auto health = m_pGameObject->GetComponent<dae::HealthCp>())
	{
		health->SetAmount(0);
	}
}

PointCommand::PointCommand(GameObject* gameObj)
{
	m_pGameObject = gameObj;
}

void PointCommand::Execute()
{
	if (!m_pGameObject || m_pGameObject->NeedsDeleting() || !m_pGameObject->GetScene()->IsActive()) return;

	if (GetKeyPressed()) return;

	if (const auto points = m_pGameObject->GetComponent<dae::PointsCp>())
	{
		points->ChangeAmount(1);

		m_pGameObject->NotifyObservers(ScoredPoint);

	}

	SetKeyPressed(true);
}

ShootCommand::ShootCommand(GameObject* gameObj, const glm::vec3& direction)
{
	m_pGameObject = gameObj;
	m_Direction = direction;
}

void ShootCommand::Execute()
{
	if (!m_pGameObject || m_pGameObject->NeedsDeleting() || !m_pGameObject->GetScene()->IsActive()) return;

	if (GetKeyPressed()) return;


	const auto bullet = std::make_shared<Bullet>(m_Direction);
	bullet->SetTag(m_pGameObject->GetTag());


	const glm::vec3 middlePos = { m_pGameObject->GetWorldTransform().x + m_pGameObject->GetSize().x / 2 - bullet->GetSize().x / 2,
		m_pGameObject->GetWorldTransform().y + m_pGameObject->GetSize().y / 2 - bullet->GetSize().y / 2,
		0 };
	bullet->SetRelativePos(middlePos);

	m_pGameObject->GetScene()->Add(bullet);

	SetKeyPressed(true);
}

void SkipLevelCommand::Execute()
{
	if (GetKeyPressed()) return;

	auto& sceneManager = dae::SceneManager::GetInstance();
	if (sceneManager.GetActiveSceneName() == "MainMenu")
	{
		SetKeyPressed(true);
		return;
	}

	auto objects = sceneManager.GetActiveScene()->GetGameObjects();
	for (auto& o : objects)
	{
		if (!dynamic_cast<Level*>(o.get())) continue;

		const auto level = dynamic_cast<Level*>(o.get());
		level->OnLevelDestroy();
		break;
	}
	
	sceneManager.NextScene();
	if (sceneManager.GetActiveSceneName() == "WaitingScene")
	{
		sceneManager.NextScene();
	}

	objects = sceneManager.GetActiveScene()->GetGameObjects();
	for (auto& o : objects)
	{
		if (!dynamic_cast<Level*>(o.get())) continue;

		const auto level = dynamic_cast<Level*>(o.get());
		level->OnLevelLoad();
		break;
	}


	
	SetKeyPressed(true);
}

void StartGameCommand::Execute()
{
	if (GetKeyPressed()) return;
	if (dae::SceneManager::GetInstance().GetActiveSceneName() != "MainMenu")
	{
		SetKeyPressed(true);
		return;
	}


	const std::string nameScene{"Level0"};
	dae::SceneManager::GetInstance().SetActiveScene(nameScene);

	const auto objects = dae::SceneManager::GetInstance().GetActiveScene()->GetGameObjects();
	for (auto& o : objects)
	{
		if (!dynamic_cast<Level*>(o.get())) continue;

		const auto level = dynamic_cast<Level*>(o.get());
		level->OnLevelLoad();
		break;
	}

	SetKeyPressed(true);
}

void ExitGameCommand::Execute()
{
	exit(0);
}

void SwitchGameModeCommand::Execute()
{
	if (GetKeyPressed()) return;
	if (dae::SceneManager::GetInstance().GetActiveSceneName() != "MainMenu")
	{
		SetKeyPressed(true);
		return;
	}

	PlayerManager::GetInstance().SwitchGameMode();

	SetKeyPressed(true);
}
