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
#include "PlayerManager.h"
//Components
#include "AudioService.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "FPSComponent.h"
#include "RotationCp.h"

#include "GameObject.h"
#include "Scene.h"
#include "InputManager.h"

#include "GameCommands.h"
#include "Tank.h"
#include "Level.h"
#include "Menu.h"

using namespace dae;

void InitMainMenu(Scene& scene)
{
	const auto menuObj = std::make_shared<Menu>(&scene);
	scene.Add(menuObj);
}

void InitControllableObjects(Scene& scene)
{
	constexpr float speed{ 1.5f };
	glm::vec3 up = { 0.f,-speed,0.f };
	glm::vec3 down = { 0.f,speed,0.f };
	glm::vec3 right = { speed,0.f,0.f };
	glm::vec3 left = { -speed,0.f,0.f };

	//Shooting
	const float shootSpeed{ 300 };
	glm::vec3 shootUpSpeed = { 0.f, -shootSpeed, 0.f };
	glm::vec3 shootDownSpeed = { 0.f, shootSpeed, 0.f };
	glm::vec3 shootLeftSpeed = { -shootSpeed, 0.f, 0.f };
	glm::vec3 shootRightSpeed = { shootSpeed, 0.f, 0.f };

	int controllerIdx{ 0 };

	auto fontTankUI = ResourceManager::GetInstance().LoadFont("Lingua.otf", 15);

	//PREFAB RED TANK
	{
		auto tankPrefab = std::make_shared<RedTank>();
		scene.Add(tankPrefab);


		auto* moveCommandUp = new MoveCommand{ tankPrefab.get(), up };
		auto* moveCommandDown = new MoveCommand{ tankPrefab.get(), down };
		auto* moveCommandLeft = new MoveCommand{ tankPrefab.get(), left };
		auto* moveCommandRight = new MoveCommand{ tankPrefab.get(), right };

		InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_S, moveCommandDown);
		InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_W, moveCommandUp);
		InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_A, moveCommandLeft);
		InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_D, moveCommandRight);

		//Shooting
		auto* shootUp = new ShootCommand{ tankPrefab.get(), shootUpSpeed };
		auto* shootDown = new ShootCommand{ tankPrefab.get(), shootDownSpeed };
		auto* shootLeft = new ShootCommand{ tankPrefab.get(), shootLeftSpeed };
		auto* shootRight = new ShootCommand{ tankPrefab.get(), shootRightSpeed };

		InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_UP, shootUp);
		InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_DOWN, shootDown);
		InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_LEFT, shootLeft);
		InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_RIGHT, shootRight);

		PlayerManager::GetInstance().AddPlayer(tankPrefab);

		////Dying/Points logic
		//auto pHealth = std::make_shared<HealthCp>(tankPrefab.get(), 1);
		//tankPrefab->AddComponent(pHealth);

		//auto pPoints = std::make_shared<PointsCp>(tankPrefab.get(), 0);
		//tankPrefab->AddComponent(pPoints);

		//DieCommand* dieCommand = new DieCommand{ tankPrefab.get() };
		//dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_O, dieCommand);
		//PointCommand* pointCommand = new PointCommand{ tankPrefab.get() };
		//dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_P, pointCommand);

		//auto pUIObserver = std::make_shared<UI>();
		//tankPrefab->MakeObserver(pUIObserver);

		////parent->AddChild(tankPrefab.get());

		////Lives Display
		//auto redTankLivesObj = std::make_shared<GameObject>("redTank");
		//auto textRedLives = std::make_shared<UICp>(fontTankUI, "Lives: ", SDL_Color{ 255, 0, 0 },
		//	"Lives", redTankLivesObj.get());
		//redTankLivesObj->SetRelativePos({ 5, 310 });
		//redTankLivesObj->AddComponent(textRedLives);
		////parent->AddChild(redTankLivesObj.get());
		//scene.Add(redTankLivesObj);

		////Points Display
		//auto redTankPointsObj = std::make_shared<GameObject>("redTank");
		//auto textBluePoints = std::make_shared<UICp>(fontTankUI, "Points: ", SDL_Color{ 255, 0, 0 },
		//	"Points", redTankPointsObj.get());
		//redTankPointsObj->SetRelativePos({ 5, 340 });
		//redTankPointsObj->AddComponent(textBluePoints);
		////parent->AddChild(redTankPointsObj.get());
		//scene.Add(redTankPointsObj);
	}

	//BLUE TANK
	{
		
		auto blueTank = std::make_shared<BlueTank>();
		scene.Add(blueTank);

		dae::InputManager::GetInstance().AddController(controllerIdx);

		Controller::ControllerButton button{};


		auto* moveCommandDownBlue = new MoveCommand{ blueTank.get(), down };
		auto* moveCommandUpBlue = new MoveCommand{ blueTank.get(), up };
		auto* moveCommandLeftBlue = new MoveCommand{ blueTank.get(), left };
		auto* moveCommandRightBlue = new MoveCommand{ blueTank.get(), right };


		button = Controller::ControllerButton::DpadDown;
		InputManager::GetInstance().BindControllerToCommand(controllerIdx, button, moveCommandDownBlue);
		button = Controller::ControllerButton::DpadUp;
		InputManager::GetInstance().BindControllerToCommand(controllerIdx, button, moveCommandUpBlue);
		button = Controller::ControllerButton::DpadLeft;
		InputManager::GetInstance().BindControllerToCommand(controllerIdx, button, moveCommandLeftBlue);
		button = Controller::ControllerButton::DpadRight;
		InputManager::GetInstance().BindControllerToCommand(controllerIdx, button, moveCommandRightBlue);


		//Shooting
		auto* shootUp = new ShootCommand{ blueTank.get(), shootUpSpeed };
		auto* shootDown = new ShootCommand{ blueTank.get(), shootDownSpeed };
		auto* shootLeft = new ShootCommand{ blueTank.get(), shootLeftSpeed };
		auto* shootRight = new ShootCommand{ blueTank.get(), shootRightSpeed };

		button = Controller::ControllerButton::ButtonY;
		InputManager::GetInstance().BindControllerToCommand(controllerIdx, button, shootUp);
		button = Controller::ControllerButton::ButtonA;
		InputManager::GetInstance().BindControllerToCommand(controllerIdx, button, shootDown);
		button = Controller::ControllerButton::ButtonX;
		InputManager::GetInstance().BindControllerToCommand(controllerIdx, button, shootLeft);
		button = Controller::ControllerButton::RightShoulder;
		InputManager::GetInstance().BindControllerToCommand(controllerIdx, button, shootRight);


		PlayerManager::GetInstance().AddPlayer(blueTank);

		////Dying/Points logic
		//auto pHealthBlue = std::make_shared<HealthCp>(blueTank.get(), 1);
		//blueTank->AddComponent(pHealthBlue);

		//auto pPointsBlue = std::make_shared<PointsCp>(blueTank.get(), 0);
		//blueTank->AddComponent(pPointsBlue);

		//DieCommand* dieCommandBlue = new DieCommand{ blueTank.get() };
		//button = Controller::ControllerButton::ButtonY;
		//dae::InputManager::GetInstance().BindControllerToCommand(controllerIdx, button, dieCommandBlue);
		//PointCommand* pointCommandBlue = new PointCommand{ blueTank.get() };
		//button = Controller::ControllerButton::ButtonA;
		//dae::InputManager::GetInstance().BindControllerToCommand(controllerIdx, button, pointCommandBlue);

		//auto pUIObserverBlue = std::make_shared<UI>();
		//blueTank->MakeObserver(pUIObserverBlue);

		//scene.Add(blueTank);

		////Lives Display
		//auto blueTankLivesObj = std::make_shared<GameObject>("blueTank");
		//auto textBlueLives = std::make_shared<UICp>(fontTankUI, "Lives: ", SDL_Color{ 0, 0, 255 },
		//	"Lives", blueTankLivesObj.get());
		//blueTankLivesObj->SetRelativePos({ 5, 380 });
		//blueTankLivesObj->AddComponent(textBlueLives);
		//scene.Add(blueTankLivesObj);

		////Points Display
		//auto blueTankPointsObj = std::make_shared<GameObject>("blueTank");
		//auto textBluePoints = std::make_shared<UICp>(fontTankUI, "Points: ", SDL_Color{ 0, 0, 255 },
		//	"Points", blueTankPointsObj.get());
		//blueTankPointsObj->SetRelativePos({ 5, 410 });
		//blueTankPointsObj->AddComponent(textBluePoints);
		//scene.Add(blueTankPointsObj);
	}
}

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
	gameObj->AddChild(logoObj.get());


	const auto textObj = std::make_shared<GameObject>();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	const auto to = std::make_shared<TextComponent>(textObj.get(), "Programming 4 Assignment", font, SDL_Color{ 255, 255, 255 });
	textObj->SetRelativePos({ 80, 20 });
	textObj->AddComponent(to);
	scene.Add(textObj);
	gameObj->AddChild(textObj.get());


	const auto fpsObj = std::make_shared<GameObject>();
	auto fontFPS = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 15);
	const auto fpsCounter = std::make_shared<FPSComponent>(fontFPS, fpsObj.get());
	fpsObj->SetRelativePos({ 7, 10 });
	fpsObj->AddComponent(fpsCounter);
	scene.Add(fpsObj);
	gameObj->AddChild(fpsObj.get());

	InitControllableObjects(scene);
}


void ExplainControls()
{
	std::cout << "-----TRON BATTLETANKS-----\nControls:\n" 
	<<	"Moving - WASD\n" << "Shooting(has sound) - Arrow Keys\n";
}

void LoadGameScene()
{
	auto& mainMenuScene = SceneManager::GetInstance().CreateScene("MainMenu");
	InitMainMenu(mainMenuScene);

	auto& sceneLevel0 = SceneManager::GetInstance().CreateScene("Level0");
	const auto levelObj = std::make_shared<Level>(
		ResourceManager::GetInstance().ParseCsv("../Data/Resources/LevelLayout0.csv"), &sceneLevel0);
	sceneLevel0.Add(levelObj);

	auto& sceneLevel1 = SceneManager::GetInstance().CreateScene("Level1");
	const auto levelObj1 = std::make_shared<Level>(
		ResourceManager::GetInstance().ParseCsv("../Data/Resources/LevelLayout1.csv"), &sceneLevel1);
	sceneLevel1.Add(levelObj1);

	auto& sceneLevel2 = SceneManager::GetInstance().CreateScene("Level2");
	const auto levelObj2 = std::make_shared<Level>(
		ResourceManager::GetInstance().ParseCsv("../Data/Resources/LevelLayout2.csv"), &sceneLevel2);
	sceneLevel2.Add(levelObj2);

	auto& waitingScene = SceneManager::GetInstance().CreateScene("WaitingScene");
	InitControllableObjects(waitingScene);

	mainMenuScene.SetActive(true);
	
	auto* skipLevel = new SkipLevelCommand{};
	dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_N, skipLevel);

	auto* startGame = new StartGameCommand{};
	dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_SPACE, startGame);

	auto* exitGame = new ExitGameCommand{};
	dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_ESCAPE, exitGame);

	auto* switchGameMode = new SwitchGameModeCommand{};
	dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_TAB, switchGameMode);

	ExplainControls();
}

std::shared_ptr<Audio> Locator::service_;

void load()
{
	//LoadDaeScene();
	LoadGameScene();

	// Initialize the audio service
	Locator::initialize();
	std::shared_ptr<Audio> audio = std::make_shared<Audio>();
	Locator::provide(audio);

	Locator::getAudio().addSound("../Data/Resources/Sounds/Shoot.wav");
}

int main(int, char* []) 
{
	Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}