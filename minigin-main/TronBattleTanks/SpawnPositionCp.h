#pragma once
#include <vector>
#include <glm/vec2.hpp>

#include "BaseComponent.h"

class SpawnPositionCp  : public dae::ComponentBase
{
public:
	SpawnPositionCp(dae::GameObject* owner);

	void AddPos(const glm::vec2& pos) { m_SpawnPositions.emplace_back(pos); }
	std::vector<glm::vec2> GetPos() const { return m_SpawnPositions; }
private:
	std::vector<glm::vec2> m_SpawnPositions{};
};

class PlayerSpawnPosCp final : public SpawnPositionCp
{
public:
	PlayerSpawnPosCp(dae::GameObject* owner);
};

class EnemySpawnPosCp final : public SpawnPositionCp
{
public:
	EnemySpawnPosCp(dae::GameObject* owner);
};