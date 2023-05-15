#include <stdexcept>
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <chrono>
#include "Minigin.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "EventQueue.h"
#include "EngineEvents.h"

SDL_Window* g_window{};

void PrintSDLVersion()
{
	SDL_version version{};
	SDL_VERSION(&version);
	printf("We compiled against SDL version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	SDL_GetVersion(&version);
	printf("We are linking against SDL version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_IMAGE_VERSION(&version);
	printf("We compiled against SDL_image version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	version = *IMG_Linked_Version();
	printf("We are linking against SDL_image version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_TTF_VERSION(&version)
	printf("We compiled against SDL_ttf version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	version = *TTF_Linked_Version();
	printf("We are linking against SDL_ttf version %u.%u.%u.\n",
		version.major, version.minor, version.patch);
}

dae::Minigin::Minigin(const std::string &dataPath)
{
	PrintSDLVersion();
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	g_window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (g_window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(g_window);

	ResourceManager::GetInstance().Init(dataPath);
}

dae::Minigin::~Minigin()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(g_window);
	g_window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run(const std::function<void()>& load)
{
    // create an instance of EventQueue
    auto& event_queue = EventQueue<Event, float>::GetInstance();

    load();

    // create a thread for processing events
    std::thread event_thread([&]() 
	{
		while (event_queue.has_events()) 
		{
		    event_queue.process();
		    std::this_thread::sleep_for(std::chrono::milliseconds(10)); // avoid spinning
		}
	});

    auto& renderer = Renderer::GetInstance();
    auto& sceneManager = SceneManager::GetInstance();
    auto& input = InputManager::GetInstance();

    const float wantedFps{ 60.f };
    const int frameTimeMs{ int(1000 / wantedFps) };

    bool doContinue = true;
    auto lastTime = std::chrono::high_resolution_clock::now();
    while (doContinue)
    {
        const auto currentTime = std::chrono::high_resolution_clock::now();
        const float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
        lastTime = currentTime;

        // process events
        while (event_queue.has_events()) 
		{
            const auto event_time = event_queue.next_time();
            if (event_time > deltaTime) 
			{
                // no events before the next frame
                break;
            }
            event_queue.process_next();
        }

        doContinue = input.ProcessInput();
        sceneManager.Update(deltaTime);
        renderer.Render();

        const auto sleepTime = currentTime + std::chrono::milliseconds(frameTimeMs) -
            std::chrono::high_resolution_clock::now();
        std::this_thread::sleep_for(sleepTime);
    }

    // wait for the event thread to finish
    event_thread.join();
}

