#pragma once
#include "glm/vec3.hpp"


class GameObject;

class Command
{
public:
	virtual ~Command() = default;
	virtual void Execute() = 0;

protected:
	GameObject* GetGameActor() const { return m_pGameObject; }

protected:
	GameObject* m_pGameObject{};

};

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