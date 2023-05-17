#include "SpawnPositionCp.h"

SpawnPositionCp::SpawnPositionCp(dae::GameObject* owner):
ComponentBase(owner)
{}

PlayerSpawnPosCp::PlayerSpawnPosCp(dae::GameObject* owner):
SpawnPositionCp(owner)
{}

EnemySpawnPosCp::EnemySpawnPosCp(dae::GameObject* owner) :
	SpawnPositionCp(owner)
{}