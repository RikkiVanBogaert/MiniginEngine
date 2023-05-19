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

		void AddComponent(const std::shared_ptr<ComponentBase>& component);
		void RemoveComponent(const std::shared_ptr<ComponentBase>& component);

		template <typename T>
		T* GetComponent()
		{
			for (const auto component : m_pComponents)
			{
				if (typeid(*component) == typeid(T))
				{
					return static_cast<T*>(component.get());
				}
			}
			return nullptr;
		}

		template <typename T>
		T* GetComponentInChildren()
		{
			T cp{};
			for(auto c : m_pChildren)
			{
				cp = c->GetComponent<T>();
				if (cp) return cp;
			}
			return cp;
		}

		void MarkForDeletion();
		bool NeedsDeleting() const;

		void SetRelativePos(const glm::vec2& pos);
		void UpdateWorldPos();
		void SetFlag();

		glm::vec2 GetWorldTransform();
		glm::vec2 GetRelativeTransform() const;
		void SetSize(const glm::vec2& size) { m_Size = size; }
		glm::vec2 GetSize() const { return m_Size; }

		//Parent stuff
		void SetParent(GameObject* parent);
		GameObject* GetParent() const;
		void AddChild(std::shared_ptr<GameObject> child);
		std::vector<GameObject*> GetChildren() const;

		//Observer/Subject
		void MakeObserver(const std::shared_ptr<Observer>& observer);
		void NotifyObservers(const ObserverEvent& event) const;
		void SetTag(const std::string& tag) { m_Tag = tag; }
		std::string GetTag() const { return m_Tag; }

		void SetScene(Scene* scene);
		Scene* GetScene() const;

		GameObject(const std::string& tag = "noTag");
		virtual ~GameObject() = default;
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	protected:
		std::unique_ptr<Subject> m_pSubject;


	private:
		Scene* m_pScene{};

		//Put all these in one Transform struct
		glm::vec2 m_WorldTransform{};
		glm::vec2 m_RelativeTransform{};
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
