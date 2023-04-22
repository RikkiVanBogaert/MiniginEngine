#pragma once
#include "BaseComponent.h"
#include "TextComponent.h"
#include <string>
#include <SDL_ttf.h>

namespace dae
{
	//class TextComponent;
	class Font;

	class UICp final : public ComponentBase
	{
	public:
		UICp(std::shared_ptr<Font> font, const std::string& text, const SDL_Color& color, 
			const std::string& type, GameObject* owner);

		virtual void Update(float deltaTime) override;
		virtual void Render() const override;

		void SetText(const std::string& text) { m_pTextCp->SetText(text); }
		std::string GetBeginText() const { return m_pTextCp->GetBeginText(); }
		std::string GetType() const { return m_Type; }

	private:
		std::unique_ptr<TextComponent> m_pTextCp{};
		std::string m_Type{};
	};
}

