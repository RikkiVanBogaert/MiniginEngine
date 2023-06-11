#pragma once
#include <memory>
#include <SDL_pixels.h>
#include <vector>
#include <sstream>

#include "BaseComponent.h"

namespace dae
{
	class Font;
	class TextComponent;
}

class HighScoresCp final : public dae::ComponentBase
{
public:
	HighScoresCp(dae::GameObject* owner, const std::shared_ptr<dae::Font>& font, const SDL_Color& color);

	void Update(float deltaTime) override;
	void Render() const override;
	std::string GetName() const { return m_Name; }
	bool IsNameSet() const { return m_NameSet; }

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
	void WriteToHighScores(const std::string& name) const;
	void SortAndGetNames(const std::string& filename);
	void ShowHighScores() const;
	int GetAmountHighScores() const;

};

