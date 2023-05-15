#pragma once
#include "GameObject.h"
#include "TextureComponent.h"
#include <vector>
#include <memory>


class Level final : public dae::GameObject
{
public:
	Level(const std::vector<int>& map, dae::Scene* scene);
	//virtual ~Level() = default;

	virtual void Update(float deltaTime) override;

	bool CollisionHit(GameObject* object, const glm::vec2& dir);
	bool HitWall(const glm::vec2& start, const glm::vec2& end);

	glm::vec2 GetRandomSpawnPos() const;

	void OnLevelLoad();
	void OnLevelDestroy();

private:
	std::vector<std::shared_ptr<GameObject>> m_pLevelObjects{};
	std::vector<GameObject*> m_pWalls;
	std::vector<GameObject*> m_pPaths;
	std::vector<GameObject*> m_pTeleport;

	std::vector<glm::vec2> m_SpawnPosPlayers{};
	std::vector<glm::vec2> m_SpawnPosBlueTanks{};

	void CreateMap(const std::vector<int>& map, int columns);
	void InitHUDSinglePlayer();

	void UpdateBullets();
	bool CheckTeleportCollision(const glm::vec2& rayPoint);

	void LoadSinglePlayer() const;
	void LoadCoop() const;
	void LoadVersus() const;

	//std::shared_ptr<GameObject> pPointText;

};

