#pragma once
#include <memory>
#include <SDL_pixels.h>
#include <string>

#include "BaseComponent.h"

namespace dae
{
	class Font;
	class TextComponent;
}

class NameCp final : public dae::ComponentBase
{
public:
	NameCp(dae::GameObject* owner, const std::string& text, std::shared_ptr<dae::Font> font, const SDL_Color& color);

	void Update(float deltaTime) override;
	void Render() const override;
	std::string GetName() const { return m_Name; }

private:
	std::unique_ptr<dae::TextComponent> m_pText;
	std::string m_Name{};
	float m_Timer{};

	void EnterName(float deltaTime);
};

