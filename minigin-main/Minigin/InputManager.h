#pragma once
#include "Singleton.h"
#include "Controller.h"
#include "Commands.h"

#include <memory>
#include <map>
#include <vector>


namespace dae
{
	class GameObject;

	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		void AddController(unsigned int id);
		void BindControllerToCommand(unsigned int controllerId, Controller::ControllerButton& button, Command* command);
		void BindKeyToCommand(const Uint8& key, Command* command);
		void UnbindCommand(Command* command);
		//void UnbindAllCommands();
		void UpdateControllers();

	private:
		//Controller
		using ControllerKey = std::pair<unsigned int, Controller::ControllerButton>;
		using CommandsMap = std::map<ControllerKey, std::unique_ptr<Command>>;
		std::vector<std::unique_ptr<Controller>> m_Controllers{};
		CommandsMap m_ControllerCommands{};

		//Keyboard
		using KeyboardCommands = std::map<Uint8, std::unique_ptr<Command>>;
		KeyboardCommands m_KeyCommands;

		void ProcessInputControllers();
		void ProcessInputKeyboard();
	};

}
