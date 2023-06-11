#pragma once
#include "Singleton.h"
#include "Commands.h"
#include "Controller.h"

#include <map>
#include <vector>
#include <glm/vec2.hpp>



namespace dae
{
	class GameObject;

	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		void AddController(unsigned int id);
		void BindControllerToCommand(unsigned int controllerId, Controller::ControllerButton& button, const std::shared_ptr<Command>& command);
		void BindControllerToCommand(unsigned int controllerId, Controller::ControllerStick& stick, const std::shared_ptr<Command>& command);
		void BindKeyToCommand(const Uint8& key, const std::shared_ptr<Command>& command);
		void UnbindCommand(const std::shared_ptr<Command>& command);
		void UpdateControllers() const;

		glm::vec2 GetControllerStickValues(unsigned int controllerId, Controller::ControllerStick stick) const;

	private:
		//Controller----
		std::vector<std::unique_ptr<Controller>> m_Controllers{};
		//Buttons
		using ControllerButtonKey = std::pair<unsigned int, Controller::ControllerButton>;
		using ButtonCommandsMap = std::map<ControllerButtonKey, std::shared_ptr<Command>>;
		ButtonCommandsMap m_ControllerButtonCommands{};
		//Sticks
		using ControllerStickKey = std::pair<unsigned int, Controller::ControllerStick>;
		using StickCommandsMap = std::map<ControllerStickKey, std::shared_ptr<Command>>;
		StickCommandsMap m_ControllerStickCommands{};

		//Keyboard
		using KeyboardCommands = std::map<Uint8, std::shared_ptr<Command>>;
		KeyboardCommands m_KeyCommands;

		void ProcessInputControllers();
		void ProcessInputKeyboard() const;
	};

}
