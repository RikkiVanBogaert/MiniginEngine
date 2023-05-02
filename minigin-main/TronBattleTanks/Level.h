#pragma once
#include "GameObject.h"
#include "TextureComponent.h"
#include <vector>
#include <memory>

namespace dae
{
	class Scene;
}

class Level final : public GameObject
{
public:
	Level(std::vector<int> map);
	virtual ~Level() {};

	virtual void Update(float deltaTime) override;

	bool CollisionHit(GameObject* object, const glm::vec3& dir);
	glm::vec3 GetRandomSpawnPos() const;

	void SkipLevel();
	
	void SetScene(dae::Scene* scene);
	dae::Scene* GetScene();

private:
	std::vector<std::shared_ptr<GameObject>> m_pBlocks{};
	std::vector<GameObject*> m_pWalls;
	std::vector<GameObject*> m_pPaths;
	std::vector<GameObject*> m_pTeleport;

	dae::Scene* m_pScene{};

	int m_CurrentLevel{0};

	void CreateMap(std::vector<int> map, int columns);
	
	void UpdateBullets();
	bool CheckTeleportCollision(const glm::vec2& rayPoint);

};

