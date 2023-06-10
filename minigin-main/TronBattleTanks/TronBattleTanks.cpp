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

void Test()
{
	auto& scene = SceneManager::GetInstance().CreateScene("Test");
	scene.SetActive(true);
	CreateTankKeyboardAndController(scene);

}

void LoadNewScene()
{
	auto& startScene = SceneManager::GetInstance().CreateScene("MainMenu");

	auto& waitingScene = SceneManager::GetInstance().CreateScene("WaitingScene");
	CreateTankKeyboardAndController(waitingScene);
	CreateTankController(waitingScene);

	CreateMainMenu(startScene);
	startScene.SetActive(true);

	SceneManager::GetInstance().CreateScene("Level0");
	
	SceneManager::GetInstance().CreateScene("Level1");

	SceneManager::GetInstance().CreateScene("Level2");

	SceneManager::GetInstance().CreateScene("GameOver");

	//INPUT
	const auto skipLevel = std::make_shared<SkipLevelCommand>();
	InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_N, skipLevel);

	const auto resetGame = std::make_shared<ResetGameCommand>();
	InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_R, resetGame);

	const auto muteUnmute = std::make_shared<MuteCommand>();
	InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_M, muteUnmute);

	const int amountControllers = PlayerManager::GetInstance().GetControllerIdx();
	for (int i{}; i < amountControllers; ++i)
	{
		Controller::ControllerButton button = Controller::ControllerButton::ButtonY;
		InputManager::GetInstance().BindControllerToCommand(i, button, skipLevel);

		button = Controller::ControllerButton::ButtonB;
		InputManager::GetInstance().BindControllerToCommand(i, button, resetGame);

		button = Controller::ControllerButton::Start;
		InputManager::GetInstance().BindControllerToCommand(i, button, muteUnmute);
	}

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
	LoadNewScene();
	//Test();

#if _DEBUG
	ServiceLocator::RegisterSoundSystem(
		std::make_unique<LoggingSoundSystem>(std::make_unique<SDLSoundSystem>()));
#else
	ServiceLocator::RegisterSoundSystem(std::make_unique<SDLSoundSystem>());
#endif
	auto& ss = ServiceLocator::GetSoundSystem();
	ss.AddSound("../Data/Resources/Sounds/Shoot.wav");
	ss.AddSound("../Data/Resources/Sounds/Background.mp3");
}

int main(int, char* []) 
{
	Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}