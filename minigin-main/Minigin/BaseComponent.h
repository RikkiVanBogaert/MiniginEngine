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


		virtual void Update(float ){}
		virtual void FixedUpdate(float ){}
		virtual void Render() const {}

	protected:
		GameObject* m_pOwner{};
		bool m_NeedsUpdate{ true };

	};

}