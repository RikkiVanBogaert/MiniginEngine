#pragma once
#include "BaseComponent.h"
#include "TextComponent.h"
#include <string>
#include <SDL_ttf.h>

#include "CounterCp.h"
#include "ObserverEvent.h"

class PointsCp;
class PlayerLivesCp;
class HealthCp;

namespace dae
{
	class Subject;
	class CounterCp;
	class Font;
}

	class UICounterCp : public dae::ComponentBase
	{
	public:
		UICounterCp(dae::GameObject* owner, const std::string& text, std::shared_ptr<dae::Font> font,
		            const SDL_Color& color);

		virtual void Update(float deltaTime) override;
		virtual void Render() const override;
		void SetValueText(const std::string& text) const;

		void SetText(const std::string& text) const;
		std::string GetBeginText() const { return m_BeginText; }

		void UpdateSubject(std::shared_ptr<ObserverEvent> event) const;
		dae::Subject* GetSubject() const { return m_pSubject.get(); }

	private:
		std::unique_ptr<dae::TextComponent> m_pTextCp{};
		const std::string m_BeginText{};

		std::unique_ptr<dae::Subject> m_pSubject;
	};

	class UIPointsCp final : public UICounterCp
	{
	public:
		UIPointsCp(dae::GameObject* owner, const std::string& text, std::shared_ptr<dae::Font> font,
		           const SDL_Color& color, PointsCp* counter);

	private:
		PointsCp* m_pPointsCp;
	};

	class UILivesCp final : public UICounterCp
	{
	public:
		UILivesCp(dae::GameObject* owner, const std::string& text, std::shared_ptr<dae::Font> font,
		          const SDL_Color& color, PlayerLivesCp* counter);

	private:
		PlayerLivesCp* m_pPlayerLivesCp;
	};



