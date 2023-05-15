#pragma once
#include "BaseComponent.h"
#include "TextComponent.h"
#include <string>
#include <SDL_ttf.h>

namespace dae
{
	class CounterCp;
	
	class Font;

	class UICp : public ComponentBase
	{
	public:
		UICp(GameObject* owner, std::shared_ptr<Font> font, const std::string& text, const SDL_Color& color,
			const std::string& type);

		virtual void Update(float deltaTime) override;
		virtual void Render() const override;

		void SetText(const std::string& text) { m_pTextCp->SetText(text); }
		std::string GetBeginText() const { return m_pTextCp->GetBeginText(); }
		std::string GetType() const { return m_Type; }

	private:
		std::unique_ptr<TextComponent> m_pTextCp{};
		std::string m_Type{};
	};


	class UICounterCp final : public UICp
	{
	public:
		UICounterCp(GameObject* owner, std::shared_ptr<Font> font, const std::string& text, const SDL_Color& color, CounterCp* counter);

		virtual void Update(float deltaTime) override;

	private:
		CounterCp* m_pCounterCp;
	};

}

