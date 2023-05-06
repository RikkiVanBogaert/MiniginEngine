#pragma once
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

class ShootCommand final : public dae::Command
{
public:
	ShootCommand(dae::GameObject* gameObj, const glm::vec3& direction);
	virtual void Execute() override;

private:
	glm::vec3 m_Direction{};
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