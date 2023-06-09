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

void InputManager::BindControllerToCommand(unsigned int id, Controller::ControllerButton& button, std::shared_ptr<Command> command)
{
	ControllerKey key = ControllerKey(id, button);
	m_ControllerCommands.insert({ key, command });
}

void InputManager::BindKeyToCommand(const Uint8& key, std::shared_ptr<Command> command)
{
	m_KeyCommands.insert({ key, command });
}

void InputManager::UnbindCommand(Command* command)
{
	// `command` is the command object to be removed from the map
	for (auto it = m_KeyCommands.begin(); it != m_KeyCommands.end(); ++it) 
	{
		if (it->second.get() == command) 
		{
			m_KeyCommands.erase(it);
			break;  // we found the element, so we can stop iterating
		}
	}

}

//void InputManager::UnbindAllCommands()
//{
//	m_KeyCommands.clear();
//	m_ControllerCommands.clear();
//	m_Controllers.clear();
//}

void InputManager::ProcessInputControllers()
{
    for (auto& controller : m_Controllers)
    {
        for (auto& command : m_ControllerCommands)
        {
            const auto controllerKey = command.first.second;
            const unsigned int controllerId = command.first.first;
            if (controller->GetControllerIndex() == controllerId && controller->IsPressed(controllerKey))
            {
                command.second->Execute();
            }
			else if(controller->GetControllerIndex() == controllerId)
			{
				command.second->SetKeyPressed(false);
			}

        }

    }
}

void InputManager::ProcessInputKeyboard()
{
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);

	for (auto& keyCommand : m_KeyCommands)
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

void InputManager::UpdateControllers()
{
    for (auto& controller : m_Controllers)
    {
        controller->Update();
    }
}