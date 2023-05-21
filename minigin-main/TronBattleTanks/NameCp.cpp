#include "NameCp.h"

#include <iostream>

#include "TextComponent.h"

#include <memory>
#include <SDL_pixels.h>

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
    if (m_Name != "name" || m_Name  == "")
    {
        return;
    }

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
            if (e.type == SDL_KEYUP)
            {
                if (e.key.keysym.sym == SDLK_KP_ENTER || e.key.keysym.sym == SDLK_RETURN)
                {
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
        //std::cout << m_Name << '\n';
    }

    m_pText->SetText(m_Name);
}

