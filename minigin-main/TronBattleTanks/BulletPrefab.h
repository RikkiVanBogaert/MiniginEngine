#pragma once
#include "BulletCp.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "Scene.h"

static dae::GameObject* CreateBullet(dae::Scene& scene, dae::GameObject* shooter, const glm::vec2& vel, bool playerBullet = true)
{
	const auto pBullet = std::make_shared<dae::GameObject>();
	scene.Add(pBullet);

	const auto bulletTxt = std::make_shared<dae::TextureComponent>(pBullet.get());
	if(playerBullet)
	{
		bulletTxt->SetTexture("Resources/Sprites/BulletPlayer.png");
	}
	else
	{
		bulletTxt->SetTexture("Resources/Sprites/BulletNPC.png");
	}
	pBullet->AddComponent(bulletTxt);
	
	const auto bulletCp = std::make_shared<BulletCp>(pBullet.get(), shooter, vel);
	pBullet->AddComponent(bulletCp);

	return pBullet.get();
}
