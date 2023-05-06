#include "Menu.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "Scene.h"

using namespace dae;

Menu::Menu(dae::Scene* scene)
{
	SetScene(scene);
	InitMenu();
}

void Menu::InitMenu()
{
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	auto startObj = std::make_shared<GameObject>();
	auto startText = std::make_shared<TextComponent>(startObj.get(), "START (Space)", font, SDL_Color{ 255, 255, 255 });
	startObj->SetRelativePos({ 200, 40 });
	startObj->AddComponent(startText);
	GetScene()->Add(startObj);


	auto quitObj = std::make_shared<GameObject>();
	auto quitText = std::make_shared<TextComponent>(quitObj.get(), "QUIT (Esc)", font, SDL_Color{ 255, 255, 255 });
	quitObj->SetRelativePos({ 230, 160 });
	quitObj->AddComponent(quitText);
	GetScene()->Add(quitObj);

	auto gameModeObj = std::make_shared<GameObject>();
	auto gameModeText = std::make_shared<TextComponent>(gameModeObj.get(), "Switch GameMode (Shift)", font, SDL_Color{ 255, 255, 255 });
	gameModeObj->SetRelativePos({ 140, 280 });
	gameModeObj->AddComponent(gameModeText);
	GetScene()->Add(gameModeObj);


}
