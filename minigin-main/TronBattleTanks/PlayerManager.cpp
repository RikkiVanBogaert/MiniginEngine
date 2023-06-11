#include "PlayerManager.h"

#include "Scene.h"
#include "GameObject.h"
#include "PointsCp.h"
#include "PlayerLivesCp.h"

using namespace dae;

void PlayerManager::ResetPlayerVars()
{
	for (const auto& p : GetPlayers())
	{
		p->GetComponent<PointsCp>()->SetAmount(0);
		p->GetComponent<PlayerLivesCp>()->SetAmount(3);
	}
}

void PlayerManager::RemovePlayerFromScene(GameObject* player) const
{
	for (const auto& p : m_Players)
	{
		if (p.get() == player)
		{
			p->GetScene()->Remove(p);
		}
	}
}

void PlayerManager::RemoveAllPlayersFromScene()
{
	for (const auto& p : GetPlayers())
	{
		p->GetScene()->Remove(p);
	}
}
