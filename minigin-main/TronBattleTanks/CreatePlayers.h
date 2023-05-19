#pragma once
#include "PlayerManager.h"
#include "Scene.h"
#include "PlayerPrefabs.h"
using namespace dae;

//static void CreatePlayers(Scene& scene)
//{
//	
//	switch (PlayerManager::GetInstance().GetGameMode())
//	{
//	case PlayerManager::SinglePlayer:
//		CreateTankKeyboard(scene);
//		break;
//	case PlayerManager::Coop:
//		CreateTankKeyboard(scene);
//		CreateTankController(scene);
//		break;
//	case PlayerManager::Versus:
//		CreateTankKeyboard(scene);
//		CreateTankController(scene);
//		break;
//	}
//}