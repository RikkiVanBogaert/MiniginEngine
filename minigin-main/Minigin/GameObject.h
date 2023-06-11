#pragma once

#include <memory>
#include <vector>
#include <string>
#include <glm/vec2.hpp>

namespace dae
{
	class Scene;
	class ComponentBase;


	class GameObject final
	{
	public:
		GameObject(const std::string& tag = "noTag");
		~GameObject() = default;

		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void Update(float deltaTime) const;
		void FixedUpdate(float deltaTime) const;
		void Render() const;

		void AddComponent(const std::shared_ptr<ComponentBase>& component);
		void RemoveComponent(const std::shared_ptr<ComponentBase>& component);

		template <typename T>
		T* GetComponent()
		{
			for (const auto component : m_pComponents)
			{
				//cast so that it works for child/parent classes as well (see BulletCollisionCp.cpp)
				T* castComponent = dynamic_cast<T*>(component.get());
				if (castComponent != nullptr)
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

		//Parent/Children stuff
		void SetParent(GameObject* parent);
		GameObject* GetParent() const;
		void AddChild(const std::shared_ptr<GameObject>& child);
		void RemoveChild(const GameObject* child);
		void RemoveAllChildren();
		std::vector<std::shared_ptr<GameObject>> GetChildren() const;

		void MarkForDeletion();
		bool NeedsDeleting() const;

		void SetRelativePos(const glm::vec2& pos);
		void UpdateWorldPos();
		void SetDirtyFlag();
		glm::vec2 GetWorldTransform();
		glm::vec2 GetRelativeTransform() const;
		void SetSize(const glm::vec2& size) { m_Size = size; }
		glm::vec2 GetSize() const { return m_Size; }

		void SetTag(const std::string& tag) { m_Tag = tag; }
		void SetTagIncludingChildren(const std::string& tag);
		std::string GetTag() const { return m_Tag; }

		void SetScene(Scene* scene);
		Scene* GetScene() const;

	
	private:
		std::string m_Tag{};

		Scene* m_pScene{};

		std::vector<std::shared_ptr<ComponentBase>> m_pComponents{};

		GameObject* m_pParent{};
		std::vector<std::shared_ptr<GameObject>> m_pChildren{};

		glm::vec2 m_WorldTransform{};
		glm::vec2 m_RelativeTransform{};
		glm::vec2 m_Size{};
		bool m_DirtyFlag{ false };

		bool m_NeedsDeleting{};

	};
}
