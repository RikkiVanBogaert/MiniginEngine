#include "UICp.h"
#include "Font.h"
#include "Renderer.h"
#include "GameObject.h"
#include "DerCounterCps.h"

#include <chrono>

#include "CounterCp.h"
#include "GameObservers.h"
#include "Subject.h"

using namespace dae;

UICp::UICp(GameObject* owner, const std::string& text, std::shared_ptr<Font> font, const SDL_Color& color) :
	ComponentBase(owner),
	m_pTextCp{ std::make_unique<TextComponent>(owner, text, font, color) },
	m_BeginText(text)
{}


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


UICounterCp::UICounterCp(GameObject* owner, const std::string& text, std::shared_ptr<Font> font, 
	const SDL_Color& color, CounterCp* counter):
UICp(owner, text, font , color),
m_pSubject(std::make_unique<Subject>())
{
	SetText(text + std::to_string(counter->GetAmount()));
}

void UICounterCp::SetValueText(const std::string& newText)
{
	UICp::SetValueText(newText);
}

void UICounterCp::UpdateSubject(std::shared_ptr<ObserverEvent> event)
{
	m_pSubject->Notify(event);
}

UIPointsCp::UIPointsCp(GameObject* owner, const std::string& text, std::shared_ptr<Font> font, const SDL_Color& color,
                       PointsCp* counter):
UICounterCp(owner, text, font, color, counter)
{
	const auto pointsObserver = std::make_shared<PointsObserver>(counter, this);
	GetSubject()->Attach(pointsObserver);
}

UILivesCp::UILivesCp(GameObject* owner, const std::string& text, std::shared_ptr<Font> font, const SDL_Color& color,
                     LivesCp* counter) :
	UICounterCp(owner, text, font, color, counter)
{
	const auto livesObserver = std::make_shared<LivesObserver>(counter, this);
	GetSubject()->Attach(livesObserver);

}
