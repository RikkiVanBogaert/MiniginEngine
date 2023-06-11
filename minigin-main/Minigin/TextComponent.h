#pragma once
#include <string>
#include <memory>
#include <SDL_ttf.h>
#include "BaseComponent.h"

namespace dae
{
	class Font;
	class Texture2D;

	class TextComponent final: public ComponentBase
	{
	public:
		//TextComponent() = default;
		TextComponent(GameObject* owner, const std::string& text, const std::shared_ptr<Font>& font, const SDL_Color& color);

		virtual ~TextComponent() override = default;

		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

		virtual void Update(float deltaTime) override;
		virtual void Render() const override;

		void SetText(const std::string& text);
		std::string GetBeginText() const { return m_BeginText; }

		
	private:
		std::string m_Text{}, m_BeginText{};
		std::shared_ptr<Font> m_Font;
		std::shared_ptr<Texture2D> m_TextTexture;
		SDL_Color m_Color;

		bool m_NeedsUpdate{ true };
	};
}
