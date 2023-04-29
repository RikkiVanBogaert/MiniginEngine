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

	bool CollisionHit(GameObject* object, const glm::vec3& dir);

private:
	std::vector<std::unique_ptr<GameObject>> m_pBlocks{};


	std::vector<int> parse_csv(const std::string& filename);
};

