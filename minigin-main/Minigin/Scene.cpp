#include "Scene.h"
#include "GameObject.h"

#include <fstream>
#include <sstream>

using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name) {}

Scene::~Scene() = default;

void Scene::Add(std::shared_ptr<GameObject> object)
{
	object->SetScene(this);
	m_objects.emplace_back(std::move(object));
}

void Scene::Remove(std::shared_ptr<GameObject> object)
{
	m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), object), m_objects.end());
}

void Scene::RemoveAll()
{
	m_objects.clear();
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

void dae::Scene::FixedUpdate(float deltaTime)
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

std::vector<int> Scene::parse_csv(const std::string& filename)
{
	std::vector<int> result;

	// Open the file for reading
	std::ifstream file(filename);
	if (!file.is_open())
	{
		// Handle error
		std::cout << "Couldnt open file\n";
		return result;
	}

	// Read each line of the file
	std::string line;
	while (std::getline(file, line))
	{
		// Parse the line into integers
		std::stringstream ss(line);
		std::string field;
		while (std::getline(ss, field, ','))
		{
			try
			{
				result.push_back(std::stoi(field));
			}
			catch (std::invalid_argument&)
			{
				// Handle invalid data
				std::cout << "Invalid data in file\n";
			}
		}
	}

	std::cout << "File succesfully opened\n";
	return result;
}
