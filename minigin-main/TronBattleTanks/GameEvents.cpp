#include "GameEvents.h"

#include "CounterCp.h"
#include "GameObject.h"
#include "Scene.h"

void UpdateCounterEvent::FindCounter(dae::GameObject* gameObject)
{
	for (auto& object : gameObject->GetScene()->GetGameObjects())
	{
		if (object->GetTag() != gameObject->GetTag()) continue;

		if (!dynamic_cast<dae::PointsCp*>(object.get())) continue;

		m_pPointCounter = dynamic_cast<dae::PointsCp*>(object.get());
	}
}

void UpdateCounterEvent::execute()
{
	m_pPointCounter->ChangeAmount(m_AddedCounterValue);
	std::cout << "GOT " << m_AddedCounterValue << " POINTS\n";
}

