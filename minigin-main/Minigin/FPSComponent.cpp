#include "FPSComponent.h"
#include "TextComponent.h"

#include <SDL_ttf.h>
#include <chrono>

using namespace dae;


FPSComponent::FPSComponent(GameObject* owner, const std::shared_ptr<Font>& font) :
ComponentBase(owner),
m_pTextCp( std::make_unique<TextComponent>(owner, "FPS: 00", font, SDL_Color{255, 255, 0, 255}) )
{}

void FPSComponent::Update(float deltaTime)
{
	m_pTextCp->Update(deltaTime);
	UpdateFPS(deltaTime);
}

void FPSComponent::Render() const
{
	m_pTextCp->Render();
}

void FPSComponent::UpdateFPS(float) const
{
	static std::chrono::time_point<std::chrono::steady_clock> oldTime = std::chrono::high_resolution_clock::now();
	static int fps{};
	fps++;

	if (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - oldTime) >= std::chrono::seconds{ 1 }) 
	{
		oldTime = std::chrono::high_resolution_clock::now();
		m_pTextCp->SetText("FPS: " + std::to_string(fps));
		fps = 0;
	}
}