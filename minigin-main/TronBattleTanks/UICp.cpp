#pragma once
#include "UICp.h"
#include "Font.h"
#include "Renderer.h"
#include "GameObject.h"
#include "DerCounterCps.h"

#include <chrono>

#include "CounterCp.h"

using namespace dae;

UICp::UICp(GameObject* owner, std::shared_ptr<Font> font, const std::string& text, const std::string&, const SDL_Color& color) :
	ComponentBase(owner),
	m_pTextCp{ std::make_unique<TextComponent>(owner, text, font, color) }
{
	//m_pTextCp->SetText(text + value);
}


void UICp::Update(float deltaTime)
{
	m_pTextCp->Update(deltaTime);
}

void UICp::Render() const
{
	m_pTextCp->Render();
}

void UICp::SetText(const std::string& text)
{
	m_pTextCp->SetText(text);
}

void UICp::SetValueText(const std::string& text)
{
	m_pTextCp->SetText(GetBeginText() + text);
}


UICounterCp::UICounterCp(GameObject* owner, std::shared_ptr<Font> font, const std::string& text, const SDL_Color& color,
                         CounterCp* counter):
UICp(owner, font, text , "0", color),
m_pCounterCp(counter)
{
	SetText(text + std::to_string(counter->GetAmount()));
}

void UICounterCp::SetValueText(const std::string&)
{
	//auto player = GetGameObject(m_pOwner->GetScene(), m_pOwner->GetTag());
	//m_pCounterCp = player->GetComponent<PointsCp>();
	
	UICp::SetValueText(std::to_string(m_pCounterCp->GetAmount()));
}

UIPointsCp::UIPointsCp(GameObject* owner, const std::shared_ptr<Font>& font, const std::string& text, const SDL_Color& color,
	PointsCp* counter):
UICounterCp(owner, font, text, color, counter)
{}

UILivesCp::UILivesCp(GameObject* owner, const std::shared_ptr<Font>& font, const std::string& text, const SDL_Color& color,
	LivesCp* counter):
	UICounterCp(owner, font, text, color, counter)
{}
