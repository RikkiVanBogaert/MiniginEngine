#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update(float deltaTime)
{
	for (auto& scene : m_scenes)
	{
		if(scene->IsActive())
			scene->Update(deltaTime);
	}
}

void dae::SceneManager::FixedUpdate(float deltaTime)
{
	for (auto& scene : m_scenes)
	{
		if (scene->IsActive())
			scene->FixedUpdate(deltaTime);
	}
}

void dae::SceneManager::Render()
{
	for (const auto& scene : m_scenes)
	{
		if (scene->IsActive())
			scene->Render();
	}
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_scenes.push_back(scene);
	return *scene;
}

void dae::SceneManager::NextScene()
{
	m_scenes[m_ActiveScene]->SetActive(false);

	++m_ActiveScene;
	if (m_ActiveScene >= m_scenes.size())
		m_ActiveScene = 0;

	m_scenes[m_ActiveScene]->SetActive(true);
}
