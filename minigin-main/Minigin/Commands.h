#pragma once
#include "glm/vec3.hpp"

namespace dae
{
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
}