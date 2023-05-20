#pragma once
#include "BaseComponent.h"
#include "TextComponent.h"
#include <string>
#include <SDL_ttf.h>

#include "CounterCp.h"

class LivesCp;
class HealthCp;
class PointsCp;

namespace dae
{
	class CounterCp;
	
	class Font;

	class UICp : public ComponentBase
	{
	public:
		UICp(GameObject* owner, std::shared_ptr<Font> font, const std::string& text, 
			const std::string& startValue = "0", const SDL_Color& color = {255, 255, 255, 255});

		virtual void Update(float deltaTime) override;
		virtual void Render() const override;

		void SetText(const std::string& text);
		virtual void SetValueText(const std::string& text);
		std::string GetBeginText() const { return m_pTextCp->GetBeginText(); }

	private:
		std::unique_ptr<TextComponent> m_pTextCp{};
	};


	class UICounterCp : public UICp
	{
	public:
		UICounterCp(GameObject* owner, std::shared_ptr<Font> font, const std::string& text, const SDL_Color& color, CounterCp* counter);

		virtual void SetValueText(const std::string& text) override;

	private:
		CounterCp* m_pCounterCp;
	};

	class UIPointsCp final : public UICounterCp
	{
	public:
		UIPointsCp(GameObject* owner, const std::shared_ptr<Font>& font, const std::string& text,
			const SDL_Color& color, PointsCp* counter);
	};

	class UILivesCp final : public UICounterCp
	{
	public:
		UILivesCp(GameObject* owner, const std::shared_ptr<Font>& font, const std::string& text,
			const SDL_Color& color, LivesCp* counter);
	};

}

