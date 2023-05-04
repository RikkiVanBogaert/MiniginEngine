#pragma once
#include <memory>
#include <vector>
#include "Transform.h"
#include "Subject.h"


namespace dae
{
	class Scene;
	class ComponentBase;


	class GameObject
	{
	public:
		virtual void Update(float deltaTime);
		virtual void FixedUpdate(float deltaTime);
		virtual void Render() const;

		void AddComponent(std::shared_ptr<ComponentBase> component);
		void RemoveComponent(std::shared_ptr<ComponentBase> component);

		template <typename T>
		T* GetComponent()
		{
			for (auto component : m_pComponents)
			{
				if (typeid(*component) == typeid(T))
				{
					return static_cast<T*>(component.get());
				}
			}
			return nullptr;
		}

		void MarkForDeletion();
		bool NeedsDeleting();

		void SetRelativePos(const glm::vec3& pos);
		void UpdateWorldPos();
		void SetFlag();

		glm::vec3 GetWorldTransform();
		glm::vec3 GetRelativeTransform() const;
		void SetSize(const glm::vec2& size) { m_Size = size; };
		glm::vec2 GetSize() const { return m_Size; };

		//Parent stuff
		void SetParent(GameObject* parent);
		GameObject* GetParent();
		void AddChild(GameObject* child);
		std::vector<GameObject*> GetChildren() const;

		//Observer/Subject
		void MakeObserver(std::shared_ptr<Observer> observer);
		void NotifyObservers(Event event);
		void SetTag(const std::string& tag) { m_Tag = tag; };
		std::string GetTag() const { return m_Tag; };

		void SetScene(dae::Scene* scene);
		dae::Scene* GetScene();

		GameObject(const std::string& tag = "noTag");
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	protected:
		std::unique_ptr<Subject> m_pSubject;


	private:
		dae::Scene* m_pScene{};

		//Put all these in one Tranform struct
		glm::vec3 m_WorldTransform{};
		glm::vec3 m_RelativeTransform{};
		glm::vec2 m_Size{};

		std::vector<std::shared_ptr<ComponentBase>> m_pComponents{};

		GameObject* m_pParent{};
		std::vector<GameObject*> m_pChildren{};

		bool m_NeedsDeleting{};

		bool m_DirtyFlag{ false };

		std::string m_Tag{};

		void RemoveChild(GameObject* child);


	};
}
