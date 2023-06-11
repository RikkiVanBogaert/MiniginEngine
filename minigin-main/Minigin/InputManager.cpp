#include <SDL.h>

#include "InputManager.h"

#include <map>
#include <iostream>

using namespace dae;

bool InputManager::ProcessInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) 
	{
		if (e.type == SDL_QUIT) 
		{
			return false;
		}
	}

	ProcessInputKeyboard();
	ProcessInputControllers();

	return true;
}

void InputManager::AddController(unsigned int id)
{
    m_Controllers.emplace_back(std::make_unique<Controller>(id));
}


void InputManager::BindControllerToCommand(unsigned int id, Controller::ControllerButton& button, const std::shared_ptr<Command>& command)
{
	ControllerButtonKey key = ControllerButtonKey(id, button);
	m_ControllerButtonCommands.insert({ key, command });
}

void InputManager::BindControllerToCommand(unsigned id, Controller::ControllerStick& stick,
	const std::shared_ptr<Command>& command)
{
	ControllerStickKey key = ControllerStickKey(id, stick);
	m_ControllerStickCommands.insert({ key, command });
}

void InputManager::BindKeyToCommand(const Uint8& key, const std::shared_ptr<Command>& command)
{
	m_KeyCommands.insert({ key, command });
}

void InputManager::UnbindCommand(const std::shared_ptr<Command>& command)
{
	// `command` is the command object to be removed from the map
	for (auto it = m_KeyCommands.begin(); it != m_KeyCommands.end(); ++it) 
	{
		if (it->second == command) 
		{
			m_KeyCommands.erase(it);
			break;  // we found the element, so we can stop iterating
		}
	}

	for (auto it = m_ControllerButtonCommands.begin(); it != m_ControllerButtonCommands.end(); ++it)
	{
		if (it->second == command)
		{
			m_ControllerButtonCommands.erase(it);
			break;  // we found the element, so we can stop iterating
		}
	}

	for (auto it = m_ControllerStickCommands.begin(); it != m_ControllerStickCommands.end(); ++it)
	{
		if (it->second == command)
		{
			m_ControllerStickCommands.erase(it);
			break;  // we found the element, so we can stop iterating
		}
	}

}

void InputManager::ProcessInputControllers()
{
    for (const auto& controller : m_Controllers)
    {
        for (const auto& command : m_ControllerButtonCommands)
        {
            const unsigned int controllerId = command.first.first;
            const auto controllerKey = command.first.second;
            if (controller->GetControllerIndex() == controllerId && controller->IsUpThisFrame(controllerKey))
            {
                command.second->Execute();
            }
        }

		for (const auto& command : m_ControllerStickCommands)
		{
			const unsigned int controllerId = command.first.first;
			const auto controllerStick = command.first.second;
			constexpr float deadzone{ 14000 };
			if (controller->GetControllerIndex() == controllerId &&
				(abs(GetControllerStickValues(controllerId, controllerStick).x) > deadzone ||
				abs(GetControllerStickValues(controllerId, controllerStick).y) > deadzone))
			{
				command.second->Execute(true);
			}
		}
    }
}

void InputManager::ProcessInputKeyboard() const 
{
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);

	for (const auto& keyCommand : m_KeyCommands)
	{
		if (pStates[keyCommand.first])
		{
			keyCommand.second->Execute();
		}
		else
		{
			keyCommand.second->SetKeyPressed(false);
		}
	}

}

void InputManager::UpdateControllers() const
{
    for (const auto& controller : m_Controllers)
    {
        controller->Update();
    }
}

glm::vec2 InputManager::GetControllerStickValues(unsigned controllerId, Controller::ControllerStick stick) const
{
	glm::vec2 dir;

	if(stick == Controller::ControllerStick::LeftStick)
	{
		dir.x = m_Controllers[controllerId]->GetLeftStickX();
		dir.y = -m_Controllers[controllerId]->GetLeftStickY();
	}
	else
	{
		dir.x = m_Controllers[controllerId]->GetRightStickX();
		dir.y = -m_Controllers[controllerId]->GetRightStickY();
	}

	return dir;
}
