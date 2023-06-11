#include "LevelInfoCp.h"

#include "AudioService.h"
#include "GameHelpers.h"
#include "GameManager.h"
#include "Sounds.h"

LevelInfoCp::LevelInfoCp(dae::GameObject* owner):
ComponentBase(owner)
{
	auto& ss = dae::ServiceLocator::GetSoundSystem();
	ss.Play(Shoot, 0, 0, Shoot); //restart sound channel after halting it in stopSounds
	ss.Play(Background, 100, -1, Background);
}

LevelInfoCp::~LevelInfoCp()
{
	auto& ss = dae::ServiceLocator::GetSoundSystem();
	ss.StopSounds();
}

void LevelInfoCp::Update(float)
{
	CheckIfLevelComplete();
}

void LevelInfoCp::CheckIfLevelComplete() const
{
	if (!GetGameObject(GetOwner()->GetScene(), "BlueEnemy") &&
		!GetGameObject(GetOwner()->GetScene(), "Recognizer"))
	{
		GameManager::GetInstance().NextLevel();
	}
}
