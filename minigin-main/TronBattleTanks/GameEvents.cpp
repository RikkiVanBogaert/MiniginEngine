#include "GameEvents.h"

#include "CounterCp.h"
#include "GameObject.h"
#include "Scene.h"

void UpdateCounterEvent::FindCounter(dae::GameObject* gameObject)
{
	/*for (auto& object : gameObject->GetScene()->GetGameObjects())
	{
		if (object->GetTag() != gameObject->GetTag()) continue;

		if (!object->GetComponent<dae::PointsCp>()) continue;

		m_pPointCounter = object->GetComponent<dae::PointsCp>();
	}*/

	m_pPointCounter = gameObject->GetComponent<dae::PointsCp>();
}

void UpdateCounterEvent::execute()
{
	if (!m_pPointCounter) return;

	m_pPointCounter->ChangeAmount(m_AddedCounterValue);
	std::cout << "GOT " << m_AddedCounterValue << " POINTS\n";
}

