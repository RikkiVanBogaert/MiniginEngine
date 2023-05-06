#pragma once
#include "GameObject.h"
#include "TextureComponent.h"
#include <vector>
#include <memory>


class Level final : public dae::GameObject
{
public:
	Level(std::vector<int> map, dae::Scene* scene);
	virtual ~Level() {};

	virtual void Update(float deltaTime) override;

	bool CollisionHit(GameObject* object, const glm::vec2& dir);
	glm::vec2 GetRandomSpawnPos() const;

	void OnLevelLoad();
	void OnLevelDestroy();

	void SetScene(dae::Scene* scene);
	dae::Scene* GetScene();

private:
	std::vector<std::shared_ptr<GameObject>> m_pLevelObjects{};
	std::vector<GameObject*> m_pWalls;
	std::vector<GameObject*> m_pPaths;
	std::vector<GameObject*> m_pTeleport;

	dae::Scene* m_pScene{};

	glm::vec2 m_SpawnPos{};
	std::vector<glm::vec2> m_SpawnPosBlueTanks{};

	void CreateMap(std::vector<int> map, int columns);

	void UpdateBullets();
	bool CheckTeleportCollision(const glm::vec2& rayPoint);


	void LoadCharacters();
	void LoadEnemies();

};

