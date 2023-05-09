#include "Scene.h"
#include "GameObject.h"

#include <fstream>

using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name) {}

Scene::~Scene() = default;

void Scene::Add(std::shared_ptr<GameObject> object)
{
	object->SetScene(this);
	m_objects.emplace_back(std::move(object));
}

void Scene::Remove(const std::shared_ptr<GameObject>& object)
{
	m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), object), m_objects.end());
}

void Scene::RemoveAll()
{
	m_objects.clear();
	m_IsActive = false;
}

void Scene::Update(float deltaTime)
{
	for(auto& object : m_objects)
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

void dae::Scene::FixedUpdate(float deltaTime) const
{
	for (auto& object : m_objects)
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
	for (const auto& object : m_objects)
	{
		if (!object) return;

		if (object->NeedsDeleting())
		{
			continue;
		}

		object->Render();
	}
}