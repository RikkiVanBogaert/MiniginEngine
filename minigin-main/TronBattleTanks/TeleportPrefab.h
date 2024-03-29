#pragma once
#include "CollisionCp.h"
#include "GameObject.h"
#include "Scene.h"
#include "TeleportCp.h"
#include "TextureComponent.h"

namespace dae
{
	class Scene;
}

static std::shared_ptr<dae::GameObject> CreateTeleport(dae::Scene& scene, std::vector<int> teleportPlaces)
{
	auto obj = std::make_shared<dae::GameObject>();
	scene.Add(obj);

	const auto texture = std::make_shared<dae::TextureComponent>(obj.get());
	texture->SetTexture("Resources/Level/teleport.png");
	obj->AddComponent(texture);

	const auto colCp = std::make_shared<CollisionCp>(obj.get());
	colCp->AddCollider(obj.get());
	obj->AddComponent(colCp);

	const auto teleportCp = std::make_shared<TeleportCp>(obj.get(), teleportPlaces);
	obj->AddComponent(teleportCp);

	return obj;
}