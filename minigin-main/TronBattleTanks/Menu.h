#pragma once
#include "GameObject.h"
#include "TextureComponent.h"
#include <vector>
#include <memory>

class Menu final : public dae::GameObject
{
public:
	Menu(dae::Scene* scene);


private:

	void InitMenu();
};

