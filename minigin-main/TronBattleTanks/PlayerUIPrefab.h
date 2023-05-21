#pragma once
#include "GameObject.h"
#include "Scene.h"

using namespace dae;

static void CreatePlayerUI(dae::Scene& scene)
{
	auto pUI = std::make_shared<GameObject>();
	scene.Add(pUI);
}
