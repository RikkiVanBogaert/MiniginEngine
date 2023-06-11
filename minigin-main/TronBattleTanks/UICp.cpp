#include "UICp.h"
#include "Font.h"
#include "Renderer.h"
#include "GameObject.h"

#include <chrono>

#include "CounterCp.h"
#include "GameObservers.h"
#include "Subject.h"

using namespace dae;

UICounterCp::UICounterCp(GameObject* owner, const std::string& text, std::shared_ptr<Font> font, const SDL_Color& color):
ComponentBase(owner),
m_pTextCp(std::make_unique<TextComponent>(owner, text, font, color)),
m_BeginText(text),
m_pSubject(std::make_unique<Subject>())
{}

void UICounterCp::Update(float deltaTime)
{
	m_pTextCp->Update(deltaTime);
}

void UICounterCp::Render() const
{
	m_pTextCp->Render();
}

void UICounterCp::SetText(const std::string& text) const
{
	m_pTextCp->SetText(text);
}

void UICounterCp::SetValueText(const std::string& text) const
{
	m_pTextCp->SetText(GetBeginText() + text);
}

void UICounterCp::UpdateSubject(std::shared_ptr<ObserverEvent> event) const
{
	m_pSubject->Notify(event);
}

UIPointsCp::UIPointsCp(GameObject* owner, const std::string& text, std::shared_ptr<Font> font, const SDL_Color& color,
PointsCp* counter) :
	UICounterCp(owner, text, font, color),
m_pPointsCp(counter)
{
	SetText(text + std::to_string(counter->GetCounter()->GetAmount()));

	counter->SetUIPointsCp(this);

	const auto livesObserver = std::make_shared<PointsObserver>(counter, this);
	GetSubject()->Attach(livesObserver);
}


UILivesCp::UILivesCp(GameObject* owner, const std::string& text, std::shared_ptr<Font> font, const SDL_Color& color,
PlayerLivesCp* counter) :
	UICounterCp(owner, text, font, color),
m_pPlayerLivesCp(counter)
{
	SetText(text + std::to_string(counter->GetAmount()));

	counter->SetUILivesCp(this);

	const auto livesObserver = std::make_shared<LivesObserver>(counter, this);
	GetSubject()->Attach(livesObserver);

}
