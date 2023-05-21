#include "LevelInfoCp.h"

#include "GameHelpers.h"
#include "PlayerManager.h"

LevelInfoCp::LevelInfoCp(dae::GameObject* owner):
ComponentBase(owner)
{}

void LevelInfoCp::Update(float)
{
	CheckIfLevelComplete();
}

void LevelInfoCp::CheckIfLevelComplete()
{
	if (!GetGameObject(m_pOwner->GetScene(), "Enemy"))
	{
		PlayerManager::GetInstance().NextLevel();
	}
}
