#pragma once
#include <glm/vec3.hpp>

#include "Commands.h"


class Level;

class MoveCommand final : public dae::Command
{
public:
	MoveCommand(dae::GameObject* gameObj, const glm::vec3& direction);
	virtual void Execute() override;

private:
	glm::vec3 m_Direction{};
};

class DieCommand final : public dae::Command
{
public:
	DieCommand(dae::GameObject* gameObj);
	virtual void Execute() override;

};

class PointCommand final : public dae::Command
{
public:
	PointCommand(dae::GameObject* gameObj);
	virtual void Execute() override;

};


class Tank;

class ShootCommand final : public dae::Command
{
public:
	ShootCommand(Tank* gameObj, const glm::vec3& direction);
	virtual void Execute() override;

private:
	glm::vec3 m_Direction{};
	Tank* m_pTank;
};

class SkipLevelCommand final : public dae::Command
{
public:
	SkipLevelCommand() = default;
	virtual void Execute() override;

};

class StartGameCommand final : public dae::Command
{
public:
	StartGameCommand() = default; //gets gameMode as paramater
	virtual void Execute() override;
};

class ExitGameCommand final : public dae::Command
{
public:
	ExitGameCommand() = default;
	virtual void Execute() override;
};

class SwitchGameModeCommand final : public dae::Command
{
public:
	SwitchGameModeCommand() = default;
	virtual void Execute() override;
};