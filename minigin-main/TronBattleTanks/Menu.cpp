#include "Menu.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "Scene.h"
#include "PlayerManager.h"

using namespace dae;

Menu::Menu(Scene* scene)
{
	SetScene(scene);
	InitMenu();
}

void Menu::InitMenu()
{
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto smallFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);

	const auto startObj = std::make_shared<GameObject>();
	const auto startText = std::make_shared<TextComponent>(startObj.get(), "START (Space)", font, SDL_Color{ 255, 255, 255 });
	startObj->SetRelativePos({ 200, 40 });
	startObj->AddComponent(startText);
	GetScene()->Add(startObj);


	const auto quitObj = std::make_shared<GameObject>();
	const auto quitText = std::make_shared<TextComponent>(quitObj.get(), "QUIT (Esc)", font, SDL_Color{ 255, 255, 255 });
	quitObj->SetRelativePos({ 230, 160 });
	quitObj->AddComponent(quitText);
	GetScene()->Add(quitObj);

	const auto switchGameModeObj = std::make_shared<GameObject>();
	const auto switchGameModeText = std::make_shared<TextComponent>(switchGameModeObj.get(), "Switch GameMode (Shift)", font, SDL_Color{ 255, 255, 255 });
	switchGameModeObj->SetRelativePos({ 140, 280 });
	switchGameModeObj->AddComponent(switchGameModeText);
	GetScene()->Add(switchGameModeObj);

	m_pGameModeObject = std::make_shared<GameObject>();
	m_pGameModeText = std::make_shared<TextComponent>(m_pGameModeObject.get(), "SinglePlayer", smallFont, SDL_Color{ 255, 255, 255 });
	m_pGameModeObject->SetRelativePos({ 190, 320 });
	m_pGameModeObject->AddComponent(m_pGameModeText);
	GetScene()->Add(m_pGameModeObject);


	const auto nextLevelObj = std::make_shared<GameObject>();
	const auto nextLevelText = std::make_shared<TextComponent>(nextLevelObj.get(), "Next Level (N)", smallFont, SDL_Color{ 255, 255, 255 });
	nextLevelObj->SetRelativePos({ 10, 430 });
	nextLevelObj->AddComponent(nextLevelText);
	GetScene()->Add(nextLevelObj);
}

void Menu::Update(float)
{
	SetGameModeText();
}

void Menu::SetGameModeText() const
{
	switch (PlayerManager::GetInstance().GetGameMode())
	{
	case PlayerManager::SinglePlayer:
		m_pGameModeText->SetText("SinglePlayer");
		break;
	case PlayerManager::Coop:
		m_pGameModeText->SetText("Coop");
		break;
	case PlayerManager::Versus:
		m_pGameModeText->SetText("Versus");
		break;
	}
}