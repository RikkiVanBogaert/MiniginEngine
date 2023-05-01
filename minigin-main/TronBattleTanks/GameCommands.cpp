#include "GameCommands.h"
#include "GameObject.h"
#include "BaseComponent.h"
#include "CounterCp.h"

#include "Scene.h"
#include "Level.h"
#include "Bullet.h"

MoveCommand::MoveCommand(GameObject* gameObj, const glm::vec3& direction)
{
	m_pGameObject = gameObj;
	m_Direction = direction;
}

void MoveCommand::Execute()
{
	if (!m_pGameObject || m_pGameObject->NeedsDeleting()) return;

	//Rotate


	//Check level for collision
	auto sceneObjects = m_pGameObject->GetScene()->GetGameObjects();
	for (auto& o : sceneObjects)
	{
		if (!dynamic_cast<Level*>(o.get())) continue;

		auto pLevel = static_cast<Level*>(o.get());
		if (pLevel->CollisionHit(m_pGameObject, m_Direction))
			return;
		else
			break;
	}

	//Movement
	glm::vec3 pos = m_pGameObject->GetRelativeTransform();
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
	if (!m_pGameObject || m_pGameObject->NeedsDeleting()) return;

	if (auto health = m_pGameObject->GetComponent<dae::HealthCp>())
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
	if (!m_pGameObject || m_pGameObject->NeedsDeleting()) return;

	if (GetKeyPressed()) return;

	if (auto points = m_pGameObject->GetComponent<dae::PointsCp>())
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
	if (!m_pGameObject || m_pGameObject->NeedsDeleting()) return;

	if (GetKeyPressed()) return;


	auto bullet = std::make_shared<Bullet>(m_Direction);
	bullet->SetTag(m_pGameObject->GetTag());


	glm::vec3 middlePos = { m_pGameObject->GetWorldTransform().x + m_pGameObject->GetSize().x / 2 - bullet->GetSize().x / 2,
		m_pGameObject->GetWorldTransform().y + m_pGameObject->GetSize().y / 2 - bullet->GetSize().y / 2,
		0 };
	bullet->SetRelativePos(middlePos);

	m_pGameObject->GetScene()->Add(bullet);

	SetKeyPressed(true);
}