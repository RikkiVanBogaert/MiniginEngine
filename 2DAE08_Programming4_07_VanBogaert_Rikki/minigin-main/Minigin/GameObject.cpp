#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"
#include "imgui/imgui_plot.h"
#include "Observers.h"

using namespace dae;

GameObject::GameObject(const std::string& tag):
	m_Tag{tag}
{}

GameObject::~GameObject()
{}


void GameObject::AddComponent(std::shared_ptr<ComponentBase> component)
{
	m_pComponents.push_back(component);
}


void GameObject::RemoveComponent(std::shared_ptr<ComponentBase> component)
{
	m_pComponents.erase(std::remove(m_pComponents.begin(), m_pComponents.end(), component), m_pComponents.end());
}

void GameObject::MakeObserver(std::shared_ptr<Observer> observer)
{
	m_pSubject = std::make_unique<Subject>(this);
	m_pSubject->AddObserver(observer);
}

void GameObject::NotifyObservers(Event event)
{
	if (!m_pSubject) return;

	m_pSubject->NotifyObservers(event);
}

std::string GameObject::GetTag() const
{
	return m_Tag;
}

void GameObject::Update(float deltaTime)
{
	for (auto& component : m_pComponents)
	{
		component->Update(deltaTime);
	}

}

void GameObject::FixedUpdate(float deltaTime)
{
	for (auto& component : m_pComponents)
	{
		component->FixedUpdate(deltaTime);
	}
}

void GameObject::Render() const
{
	for (auto& component : m_pComponents)
	{
		component->Render();
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

GameObject* GameObject::GetParent()
{
	return m_pParent;
}

void GameObject::AddChild(GameObject* child)
{
	m_pChildren.push_back(child);
	child->SetParent(this);
}

void GameObject::RemoveChild(GameObject* child)
{
	//should remove the object from the scene aswell

	m_pChildren.erase(std::remove(m_pChildren.begin(), m_pChildren.end(), child), m_pChildren.end());
}

std::vector<GameObject*> GameObject::GetChildren() const
{
	return m_pChildren;
}

void GameObject::MarkForDeletion()
{
	m_pSubject->NotifyObservers(Event::ActorDied);
	m_NeedsDeleting = true;
}

bool GameObject::NeedsDeleting()
{
	return m_NeedsDeleting;
}

void GameObject::SetRelativePos(const glm::vec3& pos)
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

	if (!m_pParent) return; //has no parent so doesnt need to update worldPos

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

glm::vec3 GameObject::GetWorldTransform()
{
	if (m_DirtyFlag)
	{
		UpdateWorldPos();
	}

	return m_WorldTransform;
}

glm::vec3 GameObject::GetRelativeTransform() const
{
	return m_RelativeTransform;
}

