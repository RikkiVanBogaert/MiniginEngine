#include "SceneManager.h"
#include "Scene.h"

using namespace dae;

void SceneManager::Update(float deltaTime)
{
	for (auto& scene : m_scenes)
	{
		if (!scene->IsActive())
			continue;

		scene->Update(deltaTime);
		return; //only want to update 1 scene
	}
}

void SceneManager::FixedUpdate(float deltaTime)
{
	for (auto& scene : m_scenes)
	{
		if (!scene->IsActive())
			continue;

		scene->FixedUpdate(deltaTime);
		return;
	}
}

void SceneManager::Render()
{
	for (const auto& scene : m_scenes)
	{
		if (!scene->IsActive())
			continue;

		scene->Render();
		return;
	}
}

Scene& SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_scenes.push_back(scene);
	return *scene;
}

void SceneManager::NextScene()
{
	m_scenes[m_ActiveScene]->SetActive(false);

	++m_ActiveScene;
	if (m_ActiveScene >= int(m_scenes.size()))
		m_ActiveScene = 0;

	m_scenes[m_ActiveScene]->SetActive(true);
}

void SceneManager::SetActiveScene(const std::string& sceneName)
{
	m_scenes[m_ActiveScene]->SetActive(false);

	for (int i{}; i < int(m_scenes.size()); ++i)
	{
		if (m_scenes[i]->GetName() != sceneName) continue;

		m_ActiveScene = i;
		m_scenes[m_ActiveScene]->SetActive(true);
	}
}

std::string SceneManager::GetActiveSceneName() const
{
	 return m_scenes[m_ActiveScene]->GetName();
}
