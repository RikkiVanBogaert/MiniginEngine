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

#include "CounterCp.h"

using namespace dae;

UICp::UICp(GameObject* owner, std::shared_ptr<Font> font, const std::string& text, const SDL_Color& color, const std::string& type) :
	ComponentBase(owner),
	m_pTextCp{ std::make_unique<TextComponent>(owner, text, font, color) },
	m_Type{type}
{}


void UICp::Update(float deltaTime)
{
	m_pTextCp->Update(deltaTime);
}

void UICp::Render() const
{
	m_pTextCp->Render();
}

UICounterCp::UICounterCp(GameObject* owner, std::shared_ptr<Font> font, const std::string& text, const SDL_Color& color,
	 CounterCp* counter):
UICp(owner, font, text ,color, "Type"), m_pCounterCp(counter)
{}

void UICounterCp::Update(float deltaTime)
{
	//dont call setText every frame
	SetText(GetBeginText() + std::to_string(m_pCounterCp->GetAmount()));
	UICp::Update(deltaTime);
}
