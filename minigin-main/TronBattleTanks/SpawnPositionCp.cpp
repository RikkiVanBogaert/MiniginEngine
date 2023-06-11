#include "SpawnPositionCp.h"

SpawnPositionCp::SpawnPositionCp(dae::GameObject* owner):
ComponentBase(owner)
{}

PlayerSpawnPosCp::PlayerSpawnPosCp(dae::GameObject* owner):
SpawnPositionCp(owner)
{}

BlueEnemySpawnPosCp::BlueEnemySpawnPosCp(dae::GameObject* owner) :
SpawnPositionCp(owner)
{}

RecognizerSpawnPosCp::RecognizerSpawnPosCp(dae::GameObject* owner):
SpawnPositionCp(owner)
{}
