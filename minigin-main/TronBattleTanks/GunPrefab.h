#pragma once
#include "GameObject.h"
#include "Scene.h"
#include "TextureComponent.h"

namespace dae
{

	static std::shared_ptr<GameObject> CreateTankGun(Scene& scene)
	{
		auto pGun = std::make_shared<GameObject>();
		scene.Add(pGun);

		pGun->SetRelativePos({-11, -8});

		//Texture
		const auto gunTxt = std::make_shared<TextureComponent>(pGun.get());
		gunTxt->SetTexture("Resources/Sprites/RedTankGun.png");
		pGun->AddComponent(gunTxt);

		return pGun;
	}
}
