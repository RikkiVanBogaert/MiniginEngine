#include "NameCp.h"

#include <iostream>

#include "TextComponent.h"

#include <memory>
#include <SDL_pixels.h>

#include "GameHelpers.h"
#include "ResourceManager.h"

namespace dae
{
	class Font;
}

NameCp::NameCp(dae::GameObject* owner, const std::string&, std::shared_ptr<dae::Font> font, const SDL_Color& color):
ComponentBase(owner),
m_pText{ std::make_unique<dae::TextComponent>(owner, "name", font, color) },
m_Name("name")
{}

void NameCp::Update(float deltaTime)
{
	m_pText->Update(deltaTime);

	EnterName(deltaTime);
}

void NameCp::Render() const
{
	m_pText->Render();
}

void NameCp::EnterName(float deltaTime)
{
    if (m_NameSet) return;

	if(m_Timer < 1)
    {
        m_Timer += deltaTime;
        return;
    }

    m_Name = "";
    bool quit = false;
    while (!quit)
    {
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT) 
            {
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
            else if (e.type == SDL_TEXTINPUT)
            {
                m_Name += e.text.text;
            }
        }

        /*if (!m_Name.empty())
        {
            m_pText->SetText(m_Name);
            m_pText->Update(deltaTime);
            m_pText->Render();
        }*/
        //std::cout << m_Name << '\n';
    }

    m_pText->SetText(m_Name);
    m_NameSet = true;
    WriteToHighScores(m_Name);
    SortAndPrintNames("../Data/Resources/HighScores.txt");
    ShowHighScores();
}

void NameCp::WriteToHighScores(const std::string& name)
{
    auto score = GetComponentInScene<dae::TextComponent>(m_pOwner->GetScene(), "Score")->GetBeginText();

    const std::string text{ score + ", " + name };
    WriteTextToFile("../Data/Resources/HighScores.txt", text);
}


void NameCp::SortAndPrintNames(const std::string& filename)
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

void NameCp::ShowHighScores()
{
    auto mainObj = GetGameObject(m_pOwner->GetScene(), "Main");
    auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);
    glm::vec2 pos{ 350, 190 };
    for(int i{}; i < 10; ++i)
    {
        if (i >= m_HighScores.size()) return;

        const auto o = std::make_shared<dae::GameObject>();
        const std::string text = std::to_string(m_HighScores[i].score) + " - " + m_HighScores[i].name;
        const auto t = std::make_shared<dae::TextComponent>(o.get(), text, font, SDL_Color{255, 255, 50, 255});
    	o->AddComponent(t);
        o->SetTag("Highscore");
        o->SetRelativePos(pos);
        mainObj->AddChild(o);
        pos.y += 25;
    }
}
