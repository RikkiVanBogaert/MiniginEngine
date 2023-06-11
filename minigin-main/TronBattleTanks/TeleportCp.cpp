#include "TeleportCp.h"

#include "CollisionCp.h"
#include "GameHelpers.h"
#include "GameObject.h"
#include "GameManager.h"

TeleportCp::TeleportCp(dae::GameObject* owner, const std::vector<int>& teleportPlaces):
ComponentBase(owner),
m_TeleportPlaceIdxs(teleportPlaces)
{
	m_pCollisionCp = owner->GetComponent<CollisionCp>();
}

void TeleportCp::Update(float)
{
	for (auto p : GameManager::GetInstance().GetPlayers())
	{
		if (!p->GetScene()->IsActive()) continue;

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

	const auto rndNr{ rand() % m_TeleportPlaceIdxs.size() - 1 };
	const int rndSpot = m_TeleportPlaceIdxs[rndNr];

	constexpr glm::vec2 offset{ 0, 16 };
	pos = level->GetChildren()[rndSpot]->GetWorldTransform() - offset;

	return pos;
}
