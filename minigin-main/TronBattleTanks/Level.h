#pragma once
#include "GameObject.h"
#include "TextureComponent.h"
#include <vector>
#include <memory>

class Level final : public GameObject
{
public:
	Level(std::vector<int> map);
	virtual ~Level() {};

	virtual void Update(float deltaTime) override;

	bool CollisionHit(GameObject* object, const glm::vec3& dir);
	glm::vec3 GetRandomSpawnPos() const;

private:
	std::vector<std::unique_ptr<GameObject>> m_pBlocks{};

	void CreateMap(std::vector<int> map);
	
	void UpdateBullets();

};

