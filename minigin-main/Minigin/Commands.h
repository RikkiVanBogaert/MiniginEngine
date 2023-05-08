#pragma once

namespace dae
{
	class GameObject;

	class Command
	{
	public:
		Command() = default;
		virtual ~Command() = default;
		Command(const Command& other) = delete;
		Command(Command&& other) = delete;
		Command& operator=(const Command& other) = delete;
		Command& operator=(Command&& other) = delete;


		virtual void Execute() = 0;

		void SetKeyPressed(bool keyPressed) { m_KeyPressed = keyPressed; }

	protected:
		GameObject* GetGameActor() const { return m_pGameObject; }
		GameObject* m_pGameObject{};

		bool GetKeyPressed() const { return m_KeyPressed; }

	private:
		bool m_KeyPressed{};

	};
}