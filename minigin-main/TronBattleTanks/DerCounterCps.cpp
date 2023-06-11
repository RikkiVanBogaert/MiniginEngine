#include "DerCounterCps.h"

#include "GameObject.h"
#include "GameManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "UICp.h"
#include "GameOverPrefab.h"


void HealthCp::ChangeAmount(int difference)
{
	CounterCp::ChangeAmount(difference);

	if (GetCounter() > 0) return;

	m_pOwner->MarkForDeletion();
}

void HealthCp::SetAmount(int newHealth)
{
	CounterCp::SetAmount(newHealth);

	if (GetCounter() > 0) return;

	m_pOwner->MarkForDeletion();
}

void LivesCp::ChangeAmount(int difference)
{
	CounterCp::ChangeAmount(difference);
	
	if (GetCounter() < 0)
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