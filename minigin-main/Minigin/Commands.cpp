#include "Commands.h"
#include "GameObject.h"
#include "BaseComponent.h"
#include "CounterCp.h"

#include "Bullet.h"
#include "Scene.h"

MoveCommand::MoveCommand(GameObject* gameObj, const glm::vec3& direction)
{
	m_pGameObject = gameObj;
	m_Direction = direction;
}

void MoveCommand::Execute()
{
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
	if (!m_pGameObject) return;

	if(auto health = m_pGameObject->GetComponent<dae::HealthCp>())
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
	if (!m_pGameObject) return;

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
	if (GetKeyPressed()) return;

	glm::vec3 pos = m_pGameObject->GetRelativeTransform(); //put to the middle

	auto bullet = std::make_shared<Bullet>(m_Direction);
	bullet->SetTag(m_pGameObject->GetTag());
	bullet->SetRelativePos(pos);

	m_pGameObject->GetScene()->Add(bullet);

	SetKeyPressed(true);
}