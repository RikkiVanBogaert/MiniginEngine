#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
//Components
#include "TextComponent.h"
#include "TextureComponent.h"
#include "FPSComponent.h"
#include "RotationCp.h"
#include "CounterCp.h"
#include "UICp.h"

#include "GameObject.h"
#include "Scene.h"
#include "InputManager.h"
#include "Observers.h"

#include "GameCommands.h"
#include "Tank.h"
#include "Level.h"

using namespace dae;

#include <string>
#include <vector>

void InitControllableObjects(dae::Scene& scene, GameObject* parent)
{
	glm::vec3 up = { 0.f,-1.f,0.f };
	glm::vec3 down = { 0.f,1.f,0.f };
	glm::vec3 right = { 1.f,0.f,0.f };
	glm::vec3 left = { -1.f,0.f,0.f };
	int controllerIdx{ 0 };

	auto fontTankUI = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 15);

	//PREFAB RED TANK
	{
		auto tankPrefab = std::make_shared<RedTank>();
		tankPrefab->SetRelativePos({ 230, 355, 0 });
		scene.Add(tankPrefab);


		MoveCommand* moveCommandUp = new MoveCommand{ tankPrefab.get(), up };
		MoveCommand* moveCommandDown = new MoveCommand{ tankPrefab.get(), down };
		MoveCommand* moveCommandLeft = new MoveCommand{ tankPrefab.get(), left };
		MoveCommand* moveCommandRight = new MoveCommand{ tankPrefab.get(), right };

		dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_S, moveCommandDown);
		dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_W, moveCommandUp);
		dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_A, moveCommandLeft);
		dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_D, moveCommandRight);

		//Shooting
		up = { 0.f, -300.f, 0.f };
		down = { 0.f, 300.f, 0.f };
		left = { -300.f, 0.f, 0.f };
		right = { 300.f, 0.f, 0.f };
		ShootCommand* shootUp = new ShootCommand{ tankPrefab.get(), up };
		ShootCommand* shootDown = new ShootCommand{ tankPrefab.get(), down };
		ShootCommand* shootLeft = new ShootCommand{ tankPrefab.get(), left };
		ShootCommand* shootRight = new ShootCommand{ tankPrefab.get(), right };

		dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_UP, shootUp);
		dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_DOWN, shootDown);
		dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_LEFT, shootLeft);
		dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_RIGHT, shootRight);


		//Dying/Points logic
		auto pHealth = std::make_shared<HealthCp>(tankPrefab.get(), 1);
		tankPrefab->AddComponent(pHealth);

		auto pPoints = std::make_shared<PointsCp>(tankPrefab.get(), 0);
		tankPrefab->AddComponent(pPoints);

		DieCommand* dieCommand = new DieCommand{ tankPrefab.get() };
		dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_O, dieCommand);
		PointCommand* pointCommand = new PointCommand{ tankPrefab.get() };
		dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_P, pointCommand);

		auto pUIObserver = std::make_shared<UI>();
		tankPrefab->MakeObserver(pUIObserver);

		parent->AddChild(tankPrefab.get());

		//Lives Display
		auto redTankLivesObj = std::make_shared<GameObject>("redTank");
		auto textRedLives = std::make_shared<UICp>(fontTankUI, "Lives: ", SDL_Color{ 255, 0, 0 },
			"Lives", redTankLivesObj.get());
		redTankLivesObj->SetRelativePos({ 5, 310, 0 });
		redTankLivesObj->AddComponent(textRedLives);
		parent->AddChild(redTankLivesObj.get());
		scene.Add(redTankLivesObj);

		//Points Display
		auto redTankPointsObj = std::make_shared<GameObject>("redTank");
		auto textBluePoints = std::make_shared<UICp>(fontTankUI, "Points: ", SDL_Color{ 255, 0, 0 },
			"Points", redTankPointsObj.get());
		redTankPointsObj->SetRelativePos({ 5, 340, 0 });
		redTankPointsObj->AddComponent(textBluePoints);
		parent->AddChild(redTankPointsObj.get());
		scene.Add(redTankPointsObj);
	}

	//BLUE TANK
	{
		glm::vec3 downBlue = { 0.f,2.f,0.f };
		glm::vec3 upBlue = { 0.f,-2.f,0.f };
		glm::vec3 leftBlue = { -2.f,0.f,0.f };
		glm::vec3 rightBlue = { 2.f,0.f,0.f };

		auto blueTank = std::make_shared<BlueTank>();
		blueTank->SetRelativePos({ 330, 250, 0 });

		MoveCommand* moveCommandDownBlue = new MoveCommand{ blueTank.get(), downBlue };
		MoveCommand* moveCommandUpBlue = new MoveCommand{ blueTank.get(), upBlue };
		MoveCommand* moveCommandLeftBlue = new MoveCommand{ blueTank.get(), leftBlue };
		MoveCommand* moveCommandRightBlue = new MoveCommand{ blueTank.get(), rightBlue };

		dae::InputManager::GetInstance().AddController(controllerIdx);

		Controller::ControllerButton button{};

		button = Controller::ControllerButton::DpadDown;
		dae::InputManager::GetInstance().BindControllerToCommand(controllerIdx, button, moveCommandDownBlue);
		button = Controller::ControllerButton::DpadUp;
		dae::InputManager::GetInstance().BindControllerToCommand(controllerIdx, button, moveCommandUpBlue);
		button = Controller::ControllerButton::DpadLeft;
		dae::InputManager::GetInstance().BindControllerToCommand(controllerIdx, button, moveCommandLeftBlue);
		button = Controller::ControllerButton::DpadRight;
		dae::InputManager::GetInstance().BindControllerToCommand(controllerIdx, button, moveCommandRightBlue);

		scene.Add(blueTank);

		//Dying/Points logic
		auto pHealthBlue = std::make_shared<HealthCp>(blueTank.get(), 1);
		blueTank->AddComponent(pHealthBlue);

		auto pPointsBlue = std::make_shared<PointsCp>(blueTank.get(), 0);
		blueTank->AddComponent(pPointsBlue);

		DieCommand* dieCommandBlue = new DieCommand{ blueTank.get() };
		button = Controller::ControllerButton::ButtonY;
		dae::InputManager::GetInstance().BindControllerToCommand(controllerIdx, button, dieCommandBlue);
		PointCommand* pointCommandBlue = new PointCommand{ blueTank.get() };
		button = Controller::ControllerButton::ButtonA;
		dae::InputManager::GetInstance().BindControllerToCommand(controllerIdx, button, pointCommandBlue);

		auto pUIObserverBlue = std::make_shared<UI>();
		blueTank->MakeObserver(pUIObserverBlue);

		parent->AddChild(blueTank.get());
		scene.Add(blueTank);

		//Lives Display
		auto blueTankLivesObj = std::make_shared<GameObject>("blueTank");
		auto textBlueLives = std::make_shared<UICp>(fontTankUI, "Lives: ", SDL_Color{ 0, 0, 255 },
			"Lives", blueTankLivesObj.get());
		blueTankLivesObj->SetRelativePos({ 5, 380, 0 });
		blueTankLivesObj->AddComponent(textBlueLives);
		parent->AddChild(blueTankLivesObj.get());
		scene.Add(blueTankLivesObj);

		//Points Display
		auto blueTankPointsObj = std::make_shared<GameObject>("blueTank");
		auto textBluePoints = std::make_shared<UICp>(fontTankUI, "Points: ", SDL_Color{ 0, 0, 255 },
			"Points", blueTankPointsObj.get());
		blueTankPointsObj->SetRelativePos({ 5, 410, 0 });
		blueTankPointsObj->AddComponent(textBluePoints);
		parent->AddChild(blueTankPointsObj.get());
		scene.Add(blueTankPointsObj);
	}
}

void LoadDaeScene()
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	auto gameObj = std::make_shared<GameObject>();

	auto background = std::make_shared<TextureComponent>(gameObj.get());
	background->SetTexture("background.tga");
	gameObj->SetRelativePos({ 0, 0, 0 });
	gameObj->AddComponent(background);
	scene.Add(gameObj);

	auto logoObj = std::make_shared<GameObject>();
	auto logo = std::make_shared<TextureComponent>(logoObj.get());
	logo->SetTexture("logo.tga");
	logoObj->SetRelativePos({ 216, 180, 0 });
	logoObj->AddComponent(logo);
	scene.Add(logoObj);
	gameObj->AddChild(logoObj.get());


	auto textObj = std::make_shared<GameObject>();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto to = std::make_shared<TextComponent>(textObj.get(), "Programming 4 Assignment", font, SDL_Color{ 255, 255, 255 });
	textObj->SetRelativePos({ 80, 20, 0 });
	textObj->AddComponent(to);
	scene.Add(textObj);
	gameObj->AddChild(textObj.get());


	auto fpsObj = std::make_shared<GameObject>();
	auto fontFPS = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 15);
	auto fpsCounter = std::make_shared<FPSComponent>(fontFPS, fpsObj.get());
	fpsObj->SetRelativePos({ 7, 10, 0 });
	fpsObj->AddComponent(fpsCounter);
	scene.Add(fpsObj);
	gameObj->AddChild(fpsObj.get());

	InitControllableObjects(scene, gameObj.get());
}

void LoadGameScene()
{
	auto& scene = SceneManager::GetInstance().CreateScene("Level0");

	auto levelObj = std::make_shared<Level>(scene.parse_csv("../Data/Resources/LevelLayout0.csv"));
	scene.Add(levelObj);
	levelObj->SetScene(&scene);

	SkipLevelCommand* skipLevel = new SkipLevelCommand{ levelObj.get()};
	dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_N, skipLevel);

	InitControllableObjects(scene, levelObj.get());

	//scene.RemoveAll();
}

void load()
{
	//LoadDaeScene();
	LoadGameScene();
}

int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}