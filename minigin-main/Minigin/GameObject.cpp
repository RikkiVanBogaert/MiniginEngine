#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "BaseComponent.h"
#include "Observers.h"
#include "Scene.h"

using namespace dae;

GameObject::GameObject(const std::string& tag):
	m_Tag{tag}
{}


void GameObject::AddComponent(const std::shared_ptr<ComponentBase>& component)
{
	m_pComponents.push_back(component);
}


void GameObject::RemoveComponent(const std::shared_ptr<ComponentBase>& component)
{
	m_pComponents.erase(std::remove(m_pComponents.begin(), m_pComponents.end(), component), m_pComponents.end());
}


void GameObject::Update(float deltaTime)
{
	for (const auto& component : m_pComponents)
	{
		component->Update(deltaTime);
	}

	for (const auto& child : m_pChildren)
	{
		if (child->NeedsDeleting()) continue;
		child->Update(deltaTime);
	}
}

void GameObject::FixedUpdate(float deltaTime)
{
	for (const auto& component : m_pComponents)
	{
		component->FixedUpdate(deltaTime);
	}

	for (const auto& child : m_pChildren)
	{
		if (child->NeedsDeleting()) continue;
		child->FixedUpdate(deltaTime);
	}
}

void GameObject::Render() const
{
	for (auto& component : m_pComponents)
	{
		component->Render();
	}

	for (auto& child : m_pChildren)
	{
		if (child->NeedsDeleting()) continue;

		child->Render();
	}
}

void GameObject::SetParent(GameObject* parent)
{
	if (m_pParent)
	{
		m_pParent->RemoveChild(this);
	}
	m_pParent = parent;
	UpdateWorldPos();
}

GameObject* GameObject::GetParent() const
{
	return m_pParent;
}

void GameObject::AddChild(std::shared_ptr<GameObject> child)
{
	m_pChildren.push_back(child.get());
	child->SetParent(this);

	GetScene()->Add(child);
}

void GameObject::RemoveChild(GameObject* child)
{
	m_pChildren.erase(std::remove(m_pChildren.begin(), m_pChildren.end(), child), m_pChildren.end());
}

std::vector<GameObject*> GameObject::GetChildren() const
{
	return m_pChildren;
}

void GameObject::SetScene(dae::Scene* scene)
{
	m_pScene = scene;
}

dae::Scene* GameObject::GetScene() const 
{
	return m_pScene;
}

void GameObject::MarkForDeletion()
{
	m_NeedsDeleting = true;
}

bool GameObject::NeedsDeleting() const
{
	return m_NeedsDeleting;
}

void GameObject::SetRelativePos(const glm::vec2& pos)
{
	m_RelativeTransform = pos;
	
	if (!m_pParent)
	{
		m_WorldTransform = m_RelativeTransform;
	}

	SetFlag();
}

void GameObject::UpdateWorldPos()
{
	m_DirtyFlag = false;

	if (!m_pParent) return; //has no parent so doesn't need to update worldPos

	m_WorldTransform = m_pParent->GetWorldTransform() + m_RelativeTransform;
}

void GameObject::SetFlag()
{
	m_DirtyFlag = true;
	for (auto child : m_pChildren)
	{
		child->SetFlag();
	}
}

glm::vec2 GameObject::GetWorldTransform()
{
	if (m_DirtyFlag)
	{
		UpdateWorldPos();
	}

	return m_WorldTransform;
}

glm::vec2 GameObject::GetRelativeTransform() const
{
	return m_RelativeTransform;
}

