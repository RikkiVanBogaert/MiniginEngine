#include "PlayerManager.h"

void PlayerManager::SwitchGameMode()
{
	switch (m_GameMode)
	{
	case SinglePlayer:
		m_GameMode = GameMode::Coop;
		break;
	case Coop:
		m_GameMode = GameMode::Versus;
		break;
	case Versus:
		m_GameMode = GameMode::SinglePlayer;
		break;
	}
}