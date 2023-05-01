#pragma once
#include "SceneManager.h"
//#include "Level.h"

class GameObject;
namespace dae
{
	class TextComponent;

	class Scene final
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void Add(std::shared_ptr<GameObject> object);
		void Remove(std::shared_ptr<GameObject> object);
		void RemoveAll();

		void Update(float deltaTime);
		void FixedUpdate(float deltaTime);
		void Render() const;

		std::vector<std::shared_ptr<GameObject>> GetGameObjects() {	return m_objects; }
		//Level* GetActiveLevel() { return m_pActiveLevel; }
		//void SetActiveLevel(Level* level) { m_pActiveLevel = level; }
		std::vector<int> parse_csv(const std::string& filename);

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		explicit Scene(const std::string& name);

		std::string m_name;
		std::vector < std::shared_ptr<GameObject>> m_objects{};
		//Level* m_pActiveLevel;

		static unsigned int m_idCounter; 
	};

}
