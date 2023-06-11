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

#include "GameObject.h"
#include "Scene.h"

#include "MainMenuPrefab.h"
#include "PlayerPrefabs.h"

using namespace dae;

void ExplainControls()
{
	std::cout << "-----TRON BATTLETANKS-----\nControls:\n"
		<< "Moving - WASD/Left joystick\n" << "Shooting(has sound) - Arrow Keys/Right joystick\n" <<
		"Other controls are shown in game\n";
}

void Test()
{
	auto& scene = SceneManager::GetInstance().CreateScene("Test");
	scene.SetActive(true);
	CreateTankKeyboardAndController(scene);
	
}

void LoadGameScene()
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

	const int amountControllers = GameManager::GetInstance().GetControllerIdx();
	for (int i{}; i < amountControllers; ++i)
	{
		Controller::ControllerButton button = Controller::ControllerButton::ButtonY;
		InputManager::GetInstance().BindControllerToCommand(i, button, skipLevel);

		button = Controller::ControllerButton::ButtonB;
		InputManager::GetInstance().BindControllerToCommand(i, button, resetGame);

		button = Controller::ControllerButton::Back;
		InputManager::GetInstance().BindControllerToCommand(i, button, muteUnmute);
	}

	ExplainControls();
}

 //Sound statics
 std::unique_ptr<SoundSystem> ServiceLocator::m_pSsInstance{ std::make_unique<NullSoundSystem>() };
 //State statics
 std::shared_ptr<WanderState> RecognizerState::m_pWanderState = std::make_shared<WanderState>();
 std::shared_ptr<AttackState> RecognizerState::m_pAttackState = std::make_shared<AttackState>();

void load()
{
	LoadGameScene();
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