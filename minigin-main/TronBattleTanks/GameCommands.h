#pragma once
#include <glm/vec3.hpp>

#include "Commands.h"
#include "Controller.h"
#include "GameObject.h"


class Level;

class MoveCommand final : public dae::Command
{
public:
	MoveCommand(dae::GameObject* gameObj, const glm::vec2& direction, int controllerIdx = -1,
		dae::Controller::ControllerStick stick = dae::Controller::ControllerStick::LeftStick);
	virtual void Execute(bool) override;

private:
	const glm::vec2 m_Direction;
	const int m_ControllerIdx;
	const dae::Controller::ControllerStick m_ControllerStick;

	bool CheckAllMoveDirections(glm::vec2& moveDir) const;
};

class Tank;

class ShootCommand final : public dae::Command
{
public:
	ShootCommand(dae::GameObject* gameObj, const glm::vec2& direction, int controllerIdx = -1,
		dae::Controller::ControllerStick stick = dae::Controller::ControllerStick::RightStick);
	virtual void Execute(bool useStickDir = false) override;

private:
	const glm::vec2 m_Direction;
	const int m_ControllerIdx;
	const dae::Controller::ControllerStick m_ControllerStick;
};

class SkipLevelCommand final : public dae::Command
{
public:
	SkipLevelCommand() = default;
	virtual void Execute(bool) override;

};

class StartGameCommand final : public dae::Command
{
public:
	StartGameCommand() = default;
	virtual void Execute(bool) override;

};

class ExitGameCommand final : public dae::Command
{
public:
	ExitGameCommand() = default;
	virtual void Execute(bool) override;
};

class SwitchGameModeCommand final : public dae::Command
{
public:
	SwitchGameModeCommand() = default;
	virtual void Execute(bool) override;
};

class ResetGameCommand final : public dae::Command
{
public:
	ResetGameCommand() = default;
	virtual void Execute(bool) override;
};

class MuteCommand final : public dae::Command
{
public:
	MuteCommand() = default;
	virtual void Execute(bool) override;
};