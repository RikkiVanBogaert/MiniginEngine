#pragma once

namespace dae
{
	class GameObject;

	class ComponentBase
	{
	public:
		ComponentBase(GameObject* owner);
		virtual ~ComponentBase() = default;

		ComponentBase(const ComponentBase& other) = delete;
		ComponentBase(ComponentBase&& other) = delete;
		ComponentBase& operator=(const ComponentBase& other) = delete;
		ComponentBase& operator=(ComponentBase&& other) = delete;


		virtual void Update(float deltaTime);
		virtual void FixedUpdate(float deltaTime);
		virtual void Render() const;

	protected:
		bool m_NeedsUpdate{ true };
		GameObject* m_pOwner{};

	};

}