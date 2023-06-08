#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

//#pragma comment(lib, "xinput.lib")

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"

//Components
#include "AIRecognizerCp.h"
#include "AudioService.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "FPSComponent.h"
#include "RotationCp.h"

#include "GameObject.h"
#include "Scene.h"

#include "MainMenuPrefab.h"
#include "PlayerPrefabs.h"

using namespace dae;

void LoadDaeScene()
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	const auto gameObj = std::make_shared<GameObject>();

	const auto background = std::make_shared<TextureComponent>(gameObj.get());
	background->SetTexture("background.tga");
	gameObj->SetRelativePos({ 0, 0 });
	gameObj->AddComponent(background);
	scene.Add(gameObj);

	const auto logoObj = std::make_shared<GameObject>();
	const auto logo = std::make_shared<TextureComponent>(logoObj.get());
	logo->SetTexture("logo.tga");
	logoObj->SetRelativePos({ 216, 180 });
	logoObj->AddComponent(logo);
	scene.Add(logoObj);
	gameObj->AddChild(logoObj);


	const auto textObj = std::make_shared<GameObject>();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	const auto to = std::make_shared<TextComponent>(textObj.get(), "Programming 4 Assignment", 
		font, SDL_Color{ 255, 255, 255, 255 });
	textObj->SetRelativePos({ 80, 20 });
	textObj->AddComponent(to);
	scene.Add(textObj);
	gameObj->AddChild(textObj);


	const auto fpsObj = std::make_shared<GameObject>();
	auto fontFPS = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 15);
	const auto fpsCounter = std::make_shared<FPSComponent>(fpsObj.get(), fontFPS);
	fpsObj->SetRelativePos({ 7, 10 });
	fpsObj->AddComponent(fpsCounter);
	scene.Add(fpsObj);
	gameObj->AddChild(fpsObj);
}


void ExplainControls()
{
	std::cout << "-----TRON BATTLETANKS-----\nControls:\n"
		<< "Moving - WASD\n" << "Shooting(has sound) - Arrow Keys\n";
}

void Test(Scene&)
{}

void LoadNewScene()
{
	auto& startScene = SceneManager::GetInstance().CreateScene("MainMenu");
	CreateMainMenu(startScene);
	startScene.SetActive(true);

	auto& waitingScene = SceneManager::GetInstance().CreateScene("WaitingScene");
	CreateTankKeyboard(waitingScene);
	CreateTankController(waitingScene);
	CreateTankController(waitingScene);

	SceneManager::GetInstance().CreateScene("Level0");
	
	SceneManager::GetInstance().CreateScene("Level1");

	SceneManager::GetInstance().CreateScene("Level2");

	SceneManager::GetInstance().CreateScene("GameOver");

	auto* resetGame = new ResetGameCommand{};
	InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_R, resetGame);

	auto* muteUnmute = new MuteCommand{};
	InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_M, muteUnmute);

	ExplainControls();
}

//Sound statics
 std::unique_ptr<SoundSystem> ServiceLocator::m_pSsInstance{ std::make_unique<NullSoundSystem>() };
 //State statics
 std::shared_ptr<WanderState> RecognizerState::m_WanderState = std::make_shared<WanderState>();
 std::shared_ptr<AttackState> RecognizerState::m_AttackState = std::make_shared<AttackState>();

void load()
{
	//LoadDaeScene();
	//LoadGameScene();
	LoadNewScene();

#if _DEBUG
	ServiceLocator::RegisterSoundSystem(
		std::make_unique<LoggingSoundSystem>(std::make_unique<SDLSoundSystem>()));
#else
	ServiceLocator::RegisterSoundSystem(std::make_unique<SDLSoundSystem>());
#endif
	auto& ss = ServiceLocator::GetSoundSystem();
	ss.AddSound("../Data/Resources/Sounds/Shoot.wav");
}

int main(int, char* []) 
{
	Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}