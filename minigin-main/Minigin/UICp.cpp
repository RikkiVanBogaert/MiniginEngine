#pragma once
#include "UICp.h"
#include "Font.h"
#include "Texture2D.h"
#include "Renderer.h"
#include "GameObject.h"

#include <iostream>
#include <stdexcept>
#include <SDL_ttf.h>
#include <chrono>

using namespace dae;

UICp::UICp(std::shared_ptr<Font> font, const std::string& text, const SDL_Color& color, const std::string& type, GameObject* owner):
	m_pTextCp{ std::make_unique<TextComponent>(owner, text, font, color) },
	m_Type{type}
{
	m_pOwner = owner;
}


void UICp::Update(float deltaTime)
{
	m_pTextCp->Update(deltaTime);
}

void UICp::Render() const
{
	m_pTextCp->Render();
}
