#include "HighScoresCp.h"
#include "TextComponent.h"
#include "GameHelpers.h"
#include "ResourceManager.h"

#include <algorithm>
#include <iostream>
#include <memory>
#include <SDL_pixels.h>

#include "Renderer.h"


namespace dae
{
	class Font;
}

HighScoresCp::HighScoresCp(dae::GameObject* owner, const std::string&, const std::shared_ptr<dae::Font>& font, const SDL_Color& color):
ComponentBase(owner),
m_pText{ std::make_unique<dae::TextComponent>(owner, "...", font, color) }
{}

void HighScoresCp::Update(float deltaTime)
{
	m_pText->Update(deltaTime);

	EnterName(deltaTime);
}

void HighScoresCp::Render() const
{
	m_pText->Render();
}

void HighScoresCp::EnterName(float deltaTime)
{
    if (m_NameSet) return;
    //m_Name = " ";
	if(m_Timer < 1)
    {
		m_Name = " ";
        m_Timer += deltaTime;
        return;
    }

    bool quit = false;
    while (!quit)
    {
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT || e.type == SDLK_ESCAPE) 
            {
                quit = true; //bug: memory leaks when calling this before name typed
                std::exit(0);
            }
            if (e.type == SDL_KEYUP)
            {
                if (e.key.keysym.sym == SDLK_KP_ENTER || e.key.keysym.sym == SDLK_RETURN)
                {
                    if(!m_Name.empty())
						quit = true;
                }
                else if (e.key.keysym.sym == SDLK_BACKSPACE && !m_Name.empty())
                {
                    m_Name.pop_back();
                }
            }
            else if (e.type == SDL_TEXTINPUT && m_Name.size() < 16)
            {
                m_Name += e.text.text;
            }
        	//std::cout << m_Name << '\n';
            if(!m_Name.empty())
            	m_pText->SetText(m_Name);
        }
        m_pText->Update(deltaTime);
        m_pText->Render();
        dae::Renderer::GetInstance().Render();
    }

    m_pText->SetText(m_Name);
    m_NameSet = true;

    const auto explanationText = GetComponentInScene<dae::TextComponent>(m_pOwner->GetScene(), "Explanation");
    explanationText->SetText("Reset Game (R/Button B)");

    WriteToHighScores(m_Name);
    SortAndPrintNames("../Data/Resources/HighScores.txt");
    ShowHighScores();
}

void HighScoresCp::WriteToHighScores(const std::string& name) const
{
    const auto score = GetComponentInScene<dae::TextComponent>(m_pOwner->GetScene(), "Score")->GetBeginText();

    const std::string text{ score + ", " + name };
    WriteTextToFile("../Data/Resources/HighScores.txt", text);
}


void HighScoresCp::SortAndPrintNames(const std::string& filename)
{
    std::ifstream file(filename);
    std::string line;
    std::vector<Record> records;

    while (std::getline(file, line)) 
    {
        std::istringstream iss(line);
        std::string scoreStr, name;
        std::getline(iss, scoreStr, ',');
        std::getline(iss, name);
        int score = std::stoi(scoreStr);
        records.push_back({ score, name });
    }

    std::sort(records.begin(), records.end(), [](const Record& a, const Record& b) 
        {
        return a.score > b.score;
        });

    for (const auto& record : records) 
    {
        std::cout << record.score << " - " << record.name << std::endl;
    }
	m_HighScores = records;
}

void HighScoresCp::ShowHighScores() const
{
    for (int i{}; i < GetAmountHighScores(); ++i)
    {
        const auto o = GetGameObject(m_pOwner->GetScene(), "HighScore" + std::to_string(i));
        const auto textCp = o->GetComponent<dae::TextComponent>();
        const std::string text = std::to_string(m_HighScores[i].score) + " - " + m_HighScores[i].name;
        textCp->SetText(text);
    }
}

int HighScoresCp::GetAmountHighScores() const
{
    int amountHighScoresShown{};
    while(GetGameObject(m_pOwner->GetScene(), "HighScore" + std::to_string(amountHighScoresShown)) &&
        amountHighScoresShown < m_HighScores.size())
    {
        ++amountHighScoresShown;
    }
    return amountHighScoresShown;
}
