#pragma once
#include "Commands.h"

class Level;

class MoveCommand final : public Command
{
public:
	MoveCommand(GameObject* gameObj, const glm::vec3& direction);
	virtual void Execute() override;

private:
	glm::vec3 m_Direction{};
};

class DieCommand final : public Command
{
public:
	DieCommand(GameObject* gameObj);
	virtual void Execute() override;

};

class PointCommand final : public Command
{
public:
	PointCommand(GameObject* gameObj);
	virtual void Execute() override;

};

class ShootCommand final : public Command
{
public:
	ShootCommand(GameObject* gameObj, const glm::vec3& direction);
	virtual void Execute() override;

private:
	glm::vec3 m_Direction{};
};

class SkipLevelCommand final : public Command
{
public:
	SkipLevelCommand() = default;
	virtual void Execute() override;

};
