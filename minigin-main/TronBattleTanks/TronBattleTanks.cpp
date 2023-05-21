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
		font, SDL_Color{ 255, 255, 255 });
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
	<<	"Moving - WASD\n" << "Shooting(has sound) - Arrow Keys\n";
}

void Test(Scene&)
{
	
}

void LoadNewScene()
{
	auto& startScene = SceneManager::GetInstance().CreateScene("MainMenu");
	CreateMainMenu(startScene);
	startScene.SetActive(true);

	auto& waitingScene = SceneManager::GetInstance().CreateScene("WaitingScene");
	CreateTankKeyboard(waitingScene);
	CreateTankController(waitingScene);

	auto& scene = SceneManager::GetInstance().CreateScene("Level0");
	scene; //i know this sucks but idk for now
	
	auto& scene1 = SceneManager::GetInstance().CreateScene("Level1");
	scene1;

	auto& scene2 = SceneManager::GetInstance().CreateScene("Level2");
	scene2;

	auto& gameOverScene = SceneManager::GetInstance().CreateScene("GameOver");
	gameOverScene;
	//CreateGameOver(gameOverScene);

	ExplainControls();
}

 std::unique_ptr<sound_system> servicelocator::_ss_instance{ std::make_unique<null_sound_system>() };
void load()
{
	//LoadDaeScene();
	//LoadGameScene();
	LoadNewScene();

#if _DEBUG
	servicelocator::register_sound_system(
		std::make_unique<logging_sound_system>(std::make_unique<sdl_sound_system>()));
#else
	servicelocator::register_sound_system(std::make_unique<sdl_sound_system>());
#endif
	auto& ss = servicelocator::get_sound_system();
	ss.addSound("../Data/Resources/Sounds/Shoot.wav");
}

int main(int, char* []) 
{
	Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}