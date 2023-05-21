#pragma once
#include <memory>
#include <SDL_pixels.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

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
	bool m_NameSet{};
	struct Record
	{
		int score;
		std::string name;
	};
	std::vector<Record> m_HighScores{};

	void EnterName(float deltaTime);
	void WriteToHighScores(const std::string& name);


	void SortAndPrintNames(const std::string& filename);
	void ShowHighScores();
};

