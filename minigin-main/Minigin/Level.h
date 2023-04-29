#pragma once
#include "GameObject.h"
#include "TextureComponent.h"
#include <vector>
#include <memory>

class Level final : public GameObject
{
public:
	Level(const std::string& mapFile);
	virtual ~Level() {};

	virtual void Update(float deltaTime) override;

	bool CollisionHit(GameObject* object, const glm::vec3& dir);
	glm::vec3 GetRandomSpawnPos() const;

private:
	std::vector<std::unique_ptr<GameObject>> m_pBlocks{};

	void CreateMap(const std::string& mapFile);
	std::vector<int> parse_csv(const std::string& filename);

	void UpdateBullets();
};

