#pragma once
#include "BulletCp.h"
#include "CollisionCp.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "Scene.h"

static dae::GameObject* CreateBullet(dae::Scene& scene, const glm::vec2& vel)
{
	auto pBullet = std::make_shared<dae::GameObject>();
	scene.Add(pBullet);

	const auto bulletTxt = std::make_shared<dae::TextureComponent>(pBullet.get());
	bulletTxt->SetTexture("Resources/Sprites/BulletPlayer.png");
	pBullet->AddComponent(bulletTxt);
	
	const auto bulletCp = std::make_shared<BulletCp>(pBullet.get(), vel);
	pBullet->AddComponent(bulletCp);

	return pBullet.get();
}
