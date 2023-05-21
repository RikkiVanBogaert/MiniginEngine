#include "DerCounterCps.h"

#include "GameHelpers.h"
#include "GameObject.h"
#include "PlayerManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "UICp.h"
#include "GameOverPrefab.h"


void HealthCp::ChangeAmount(int difference)
{
	CounterCp::ChangeAmount(difference);

	if (GetCounter() <= 0)
	{
		m_pOwner->MarkForDeletion();
	}
}

void HealthCp::SetAmount(int newHealth)
{
	CounterCp::SetAmount(newHealth);

	if (GetCounter() <= 0)
	{
		m_pOwner->MarkForDeletion();
	}
}

void LivesCp::ChangeAmount(int difference)
{
	CounterCp::ChangeAmount(difference);
	
	if (GetCounter() < 3)
	{
		//Game Over
		dae::SceneManager::GetInstance().GetActiveScene()->RemoveAll();
		dae::SceneManager::GetInstance().SetActiveScene("GameOver");
		auto scene = dae::SceneManager::GetInstance().GetActiveScene();
		CreateGameOver(*scene);
		/*GetComponentInScene<dae::UIPointsCp>(scene, "P1Points")->SetValueText(
			std::to_string(m_pOwner->GetComponent<PointsCp>()->GetAmount()));*/
	}
	else
	{
		PlayerManager::GetInstance().ResetScene();
	}
}