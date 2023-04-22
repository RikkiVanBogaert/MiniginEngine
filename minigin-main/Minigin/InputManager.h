#pragma once
#include "Singleton.h"
#include "Controller.h"
#include "GameObject.h"
#include "Commands.h"

#include <memory>
#include <map>
#include <vector>
#include <glm/vec3.hpp>

class GameObject;


namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		void AddController(unsigned int id);
		void BindControllerToCommand(unsigned int controllerId, Controller::ControllerButton& button, Command* command);
		void BindKeyToCommand(const Uint8& key, Command* command);
		//void UnbindCommand(Command* command);
		void UpdateControllers();

	private:
		using ControllerKey = std::pair<unsigned int, Controller::ControllerButton>;
		using CommandsMap = std::map<ControllerKey, std::unique_ptr<Command>>;
		
		CommandsMap m_Commands{};
		std::vector<std::unique_ptr<Controller>> m_Controllers{};

		using KeyboardCommands = std::map<Uint8, std::unique_ptr<Command>>;

		KeyboardCommands m_KeyCommands;

		void ProcessInputControllers();
		void ProcessInputKeyboard();
	};

}
