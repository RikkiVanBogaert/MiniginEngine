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

using namespace dae;

void InitControllableObjects(dae::Scene& scene, GameObject* parent)
{
	//BLUE TANK
	glm::vec3 up = { 0.f,-1.f,0.f };
	glm::vec3 down = { 0.f,1.f,0.f };
	glm::vec3 right = { 1.f,0.f,0.f };
	glm::vec3 left = { -1.f,0.f,0.f };
	int controllerIdx{ 0 };

	auto blueTank = std::make_shared<GameObject>("blueTank");
	blueTank->SetRelativePos({ 300, 310, 0 });
	auto blueTankTxt = std::make_shared<TextureComponent>(blueTank.get());
	blueTankTxt->SetTexture("Resources/BlueTank.png");
	blueTank->AddComponent(blueTankTxt);

	MoveCommand* moveCommandUp = new MoveCommand{ blueTank.get(), up };
	MoveCommand* moveCommandDown = new MoveCommand{ blueTank.get(), down };
	MoveCommand* moveCommandLeft = new MoveCommand{ blueTank.get(), left };
	MoveCommand* moveCommandRight = new MoveCommand{ blueTank.get(), right };

	dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_S, moveCommandDown);
	dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_W, moveCommandUp);
	dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_A, moveCommandLeft);
	dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_D, moveCommandRight);

	//Dying/Points logic
	auto pHealth = std::make_shared<HealthCp>(blueTank.get(), 1 );
	blueTank->AddComponent(pHealth);

	auto pPoints = std::make_shared<PointsCp>(blueTank.get(), 0);
	blueTank->AddComponent(pPoints);

	DieCommand* dieCommand = new DieCommand{ blueTank.get() };
	dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_O, dieCommand);
	PointCommand* pointCommand = new PointCommand{ blueTank.get() };
	dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_P, pointCommand);

	auto pUIObserver = std::make_shared<UI>();
	blueTank->MakeObserver(pUIObserver);

	parent->AddChild(blueTank.get());
	scene.Add(blueTank);

	//Lives Display
	auto blueTankLivesObj = std::make_shared<GameObject>("blueTank");
	auto fontTankUI = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 15);
	auto textBlueLives = std::make_shared<UICp>(fontTankUI, "Lives: ", SDL_Color{ 0, 0, 255 },
		"Lives", blueTankLivesObj.get());
	blueTankLivesObj->SetRelativePos({ 5, 310, 0 });
	blueTankLivesObj->AddComponent(textBlueLives);
	parent->AddChild(blueTankLivesObj.get());
	scene.Add(blueTankLivesObj);

	//Points Display
	auto blueTankPointsObj = std::make_shared<GameObject>("blueTank");
	auto textBluePoints = std::make_shared<UICp>(fontTankUI, "Points: ", SDL_Color{ 0, 0, 255 },
		"Points", blueTankPointsObj.get());
	blueTankPointsObj->SetRelativePos({ 5, 340, 0 });
	blueTankPointsObj->AddComponent(textBluePoints);
	parent->AddChild(blueTankPointsObj.get());
	scene.Add(blueTankPointsObj);
	
	//RED TANK
	glm::vec3 downRed = { 0.f,2.f,0.f };
	glm::vec3 upRed = { 0.f,-2.f,0.f };
	glm::vec3 leftRed = { -2.f,0.f,0.f };
	glm::vec3 rightRed = { 2.f,0.f,0.f };

	auto redTank = std::make_shared<GameObject>("redTank");
	redTank->SetRelativePos({ 330, 250, 0 });
	auto redTankTxt = std::make_shared<TextureComponent>(redTank.get());
	redTankTxt->SetTexture("Resources/RedTank.png");
	redTank->AddComponent(redTankTxt);


	MoveCommand* moveCommandDownRed = new MoveCommand{ redTank.get(), downRed };
	MoveCommand* moveCommandUpRed = new MoveCommand{ redTank.get(), upRed };
	MoveCommand* moveCommandLeftRed = new MoveCommand{ redTank.get(), leftRed };
	MoveCommand* moveCommandRightRed = new MoveCommand{ redTank.get(), rightRed };

	dae::InputManager::GetInstance().AddController(controllerIdx);

	Controller::ControllerButton button{};

	button = Controller::ControllerButton::DpadDown;
	dae::InputManager::GetInstance().BindControllerToCommand(controllerIdx, button, moveCommandDownRed);
	button = Controller::ControllerButton::DpadUp;
	dae::InputManager::GetInstance().BindControllerToCommand(controllerIdx, button, moveCommandUpRed);
	button = Controller::ControllerButton::DpadLeft;
	dae::InputManager::GetInstance().BindControllerToCommand(controllerIdx, button, moveCommandLeftRed);
	button = Controller::ControllerButton::DpadRight;
	dae::InputManager::GetInstance().BindControllerToCommand(controllerIdx, button, moveCommandRightRed);

	scene.Add(redTank);

	//Dying/Points logic
	auto pHealthRed = std::make_shared<HealthCp>(redTank.get(), 1);
	redTank->AddComponent(pHealthRed);

	auto pPointsRed = std::make_shared<PointsCp>(redTank.get(), 0);
	redTank->AddComponent(pPointsRed);

	DieCommand* dieCommandRed = new DieCommand{ redTank.get() };
	button = Controller::ControllerButton::ButtonY;
	dae::InputManager::GetInstance().BindControllerToCommand(controllerIdx, button, dieCommandRed);
	PointCommand* pointCommandRed = new PointCommand{ redTank.get() };
	button = Controller::ControllerButton::ButtonA;
	dae::InputManager::GetInstance().BindControllerToCommand(controllerIdx, button, pointCommandRed);

	auto pUIObserverRed = std::make_shared<UI>();
	redTank->MakeObserver(pUIObserverRed);

	parent->AddChild(redTank.get());
	scene.Add(redTank);

	//Lives Display
	auto redTankLivesObj = std::make_shared<GameObject>("redTank");
	auto textRedLives = std::make_shared<UICp>(fontTankUI, "Lives: ", SDL_Color{ 255, 0, 0 },
		"Lives", redTankLivesObj.get());
	redTankLivesObj->SetRelativePos({ 5, 380, 0 });
	redTankLivesObj->AddComponent(textRedLives);
	parent->AddChild(redTankLivesObj.get());
	scene.Add(redTankLivesObj);

	//Points Display
	auto redTankPointsObj = std::make_shared<GameObject>("redTank");
	auto textRedPoints = std::make_shared<UICp>(fontTankUI, "Points: ", SDL_Color{ 255, 0, 0 },
		"Points", redTankPointsObj.get());
	redTankPointsObj->SetRelativePos({ 5, 410, 0 });
	redTankPointsObj->AddComponent(textRedPoints);
	parent->AddChild(redTankPointsObj.get());
	scene.Add(redTankPointsObj);
}

void load()
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	auto gameObj = std::make_shared<GameObject>();

	auto background = std::make_shared<TextureComponent>(gameObj.get());
	background->SetTexture("background.tga");
	gameObj->SetRelativePos({0, 0, 0});
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
	auto to = std::make_shared<TextComponent>(textObj.get(), "Programming 4 Assignment", font, SDL_Color{255, 255, 255});
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



	//gameObj->SetRelativePos({ 400, 0, 0 });
}

#include <steam_api.h>
int main(int, char*[]) {

	if (!SteamAPI_Init())
	{
		std::cerr << "Fatal Error - Steam must be running to play this game (SteamAPI_Init() failed)." << std::endl;
		return 1;
	}
	else
		std::cout << "Successfully initialized steam." << std::endl;

	
	dae::Minigin engine("../Data/");
	engine.Run(load);

	SteamAPI_Shutdown();
	return 0;

}