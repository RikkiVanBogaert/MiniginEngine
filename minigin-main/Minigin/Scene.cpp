#include "Scene.h"
#include "GameObject.h"

#include <fstream>

using namespace dae;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene() = default;

void Scene::Add(std::shared_ptr<GameObject> object)
{
	object->SetScene(this);
	m_Objects.emplace_back(std::move(object));
}

void Scene::Remove(const std::shared_ptr<GameObject>& object)
{
	if(object->GetParent())
	{
		object->GetParent()->RemoveChild(object.get());
	}

	m_Objects.erase(std::remove(m_Objects.begin(), m_Objects.end(), object), m_Objects.end());
}

void Scene::RemoveAll()
{
	m_Objects.clear();
}

void Scene::Update(float deltaTime)
{
	for(auto& object : m_Objects)
	{
		if (!object) return;

		if (object->NeedsDeleting())
		{
			Remove(object);
			continue;
		}
		object->Update(deltaTime);
	}
}

void Scene::FixedUpdate(float deltaTime) const
{
	for (auto& object : m_Objects)
	{
		if (!object) return;

		if (object->NeedsDeleting())
		{
			continue;
		}

		object->FixedUpdate(deltaTime);
	}
}

void Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		if (!object) return;

		if (object->NeedsDeleting())
		{
			continue;
		}

		object->Render();
	}
}