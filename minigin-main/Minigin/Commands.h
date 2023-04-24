#pragma once
#include "glm/vec3.hpp"


class GameObject;

class Command
{
public:
	virtual ~Command() = default;
	virtual void Execute() = 0;

	void SetKeyPressed(bool keyPressed) { m_KeyPressed = keyPressed; };

protected:
	GameObject* GetGameActor() const { return m_pGameObject; }
	GameObject* m_pGameObject{};

	bool GetKeyPressed() { return m_KeyPressed; };

private:
	bool m_KeyPressed{};

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

class ShootCommand final : public Command
{
public:
	ShootCommand(GameObject* gameObj, const glm::vec3& direction);
	virtual void Execute() override;

private:
	glm::vec3 m_Direction{};
};