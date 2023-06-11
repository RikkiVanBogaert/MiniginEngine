#include "PlayerLivesCp.h"

#include "GameManager.h"
#include "GameOverPrefab.h"

PlayerLivesCp::PlayerLivesCp(dae::GameObject* owner, int startAmount):
	dae::ComponentBase(owner),
	m_pCounterCp(std::make_unique<dae::CounterCp>(owner, startAmount)) {}

void PlayerLivesCp::ChangeAmount(int difference) const
{
	m_pCounterCp->ChangeAmount(difference);

	if (m_pCounterCp->GetAmount() < 0)
	{
		//Game Over
		dae::SceneManager::GetInstance().GetActiveScene()->RemoveAll();
		dae::SceneManager::GetInstance().SetActiveScene("GameOver");
		const auto scene = dae::SceneManager::GetInstance().GetActiveScene();
		CreateGameOver(*scene);
	}
	else
	{
		GameManager::GetInstance().ResetScene();
	}
}

void PlayerLivesCp::SetAmount(int newHealth) const
{
	if (newHealth < 0) return;

	m_pCounterCp->SetAmount(newHealth);
}