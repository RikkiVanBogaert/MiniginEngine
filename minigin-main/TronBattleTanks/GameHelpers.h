#pragma once
#include "Scene.h"
#include "GameObject.h"

#include <string>

inline dae::GameObject* GetGameObject(dae::Scene* scene, const std::string& tag)
{
	for (const auto o : scene->GetGameObjects())
	{
		if (o->GetTag() == tag)
		{
			return o.get();
		}
	}
	return nullptr;
}
