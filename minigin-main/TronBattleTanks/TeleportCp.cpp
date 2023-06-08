#include "TeleportCp.h"

#include "CollisionCp.h"
#include "GameHelpers.h"
#include "GameObject.h"
#include "PlayerManager.h"

TeleportCp::TeleportCp(dae::GameObject* owner):
ComponentBase(owner)
{
	m_pCollisionCp = owner->GetComponent<CollisionCp>();
}

void TeleportCp::Update(float)
{

	for (auto p : PlayerManager::GetInstance().GetPlayers())
	{
		//auto dir = normalize(m_pOwner->GetWorldTransform() - p->GetWorldTransform());
		if (m_pCollisionCp->DoesOverlap(p.get()))
		{
			//Teleport
			std::cout << "TELEPORT\n";
			p->SetRelativePos(GetRandomPos());
		}
	}
}

glm::vec2 TeleportCp::GetRandomPos()
{
	glm::vec2 pos{};

	const auto level = GetGameObject(m_pOwner->GetScene(), "Level");

	std::vector<int> paths{};
	for(int i{}; i < static_cast<int>(level->GetChildren().size()); ++i)
	{
		if (level->GetChildren()[i]->GetTag() != "Path") continue;

		paths.emplace_back(i);
	}

	const auto rndNr{ rand() % paths.size() - 1 };

	pos = level->GetChildren()[rndNr]->GetWorldTransform();

	return pos;
}
