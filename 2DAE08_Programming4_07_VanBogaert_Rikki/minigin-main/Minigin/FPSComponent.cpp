#pragma once
#include "FPSComponent.h"
#include "Font.h"
#include "Texture2D.h"
#include "Renderer.h"
#include "GameObject.h"
#include "TextComponent.h"

#include <iostream>
#include <stdexcept>
#include <SDL_ttf.h>
#include <chrono>

using namespace dae;


FPSComponent::FPSComponent(std::shared_ptr<Font> font, GameObject* owner) :
	m_pTextCp{ std::make_unique<TextComponent>(owner, "FPS: 00", font, SDL_Color{255, 255, 0}) }
{
	m_pOwner = owner;
}

void FPSComponent::Update(float deltaTime)
{
	m_pTextCp->Update(deltaTime);
	UpdateFPS(deltaTime);
}

void FPSComponent::Render() const
{
	m_pTextCp->Render();
}

void FPSComponent::UpdateFPS(float)
{

	static std::chrono::time_point<std::chrono::steady_clock> oldTime = std::chrono::high_resolution_clock::now();
	static int fps;
	fps++;

	if (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - oldTime) >= std::chrono::seconds{ 1 }) {
		oldTime = std::chrono::high_resolution_clock::now();
		//std::cout << "FPS: " << fps << std::endl;
		m_pTextCp->SetText("FPS: " + std::to_string(fps));
		fps = 0;
	}
}