#pragma once
#include <vector>
#include <glm/vec2.hpp>

namespace dae
{
    class GameObject;
}

class GameManager final
{
public:

    ~GameManager() = default;
    GameManager(const GameManager&) = delete;
    GameManager& operator=(const GameManager&) = delete;
    GameManager(GameManager&&) = default;
    GameManager& operator=(GameManager&&) = default;


    static GameManager& GetInstance()
    {
        static GameManager instance; 
        return instance;
    }

    enum GameMode
    {
        SinglePlayer,
        Coop,
        Versus
    };
    void SwitchGameMode();
    GameMode GetGameMode() const { return m_GameMode; }

    void AddSpawnPos(const glm::vec2 spawnPos) { m_SpawnPositions.emplace_back(spawnPos); }
    std::vector<glm::vec2> GetSpawnPositions() const { return m_SpawnPositions; }

    void LevelCreate() const;
    void ResetScene() const;

    void NextLevel() const;

    int& GetControllerIdx() { return m_ControllerIdx; }

private:
    GameManager() = default;

    GameMode m_GameMode{ SinglePlayer };
    std::vector<glm::vec2> m_SpawnPositions;

    int m_ControllerIdx{};
    
    void SkipNonLevels() const;
};

