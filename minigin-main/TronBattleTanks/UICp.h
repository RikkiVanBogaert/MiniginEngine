#pragma once
#include "BaseComponent.h"
#include "TextComponent.h"
#include <string>
#include <SDL_ttf.h>

#include "CounterCp.h"
#include "ObserverEvent.h"

class LivesCp;
class HealthCp;
class PointsCp;

namespace dae
{
	class Subject;
	class CounterCp;
	
	class Font;

	class UICp : public ComponentBase
	{
	public:
		UICp(GameObject* owner, const std::string& text, std::shared_ptr<Font> font, const SDL_Color& color = {255, 255, 255, 255});

		virtual void Update(float deltaTime) override;
		virtual void Render() const override;

		void SetText(const std::string& text);
		virtual void SetValueText(const std::string& text);
		std::string GetBeginText() const { return m_BeginText; }

	private:
		std::unique_ptr<TextComponent> m_pTextCp{};
		const std::string m_BeginText{};
	};


	class UICounterCp : public UICp
	{
	public:
		UICounterCp(GameObject* owner, const std::string& text, std::shared_ptr<Font> font, const SDL_Color& color, CounterCp* counter);

		virtual void SetValueText(const std::string& text) override;
		void UpdateSubject(std::shared_ptr<ObserverEvent> event);

	protected:
		Subject* GetSubject() const { return m_pSubject.get(); }

	private:
		std::unique_ptr<Subject> m_pSubject;
	};

	class UIPointsCp final : public UICounterCp
	{
	public:
		UIPointsCp(GameObject* owner, const std::string& text, std::shared_ptr<Font> font,
			const SDL_Color& color, PointsCp* counter);

	};

	class UILivesCp final : public UICounterCp
	{
	public:
		UILivesCp(GameObject* owner, const std::string& text, std::shared_ptr<Font> font,
			const SDL_Color& color, LivesCp* counter);
	};

}

