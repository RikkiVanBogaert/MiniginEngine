#pragma once
#include <memory>
#include <vector>
#include <glm/vec2.hpp>

namespace dae
{
    class GameObject;
}

class PlayerManager final
{
public:

    ~PlayerManager() = default;
    PlayerManager(const PlayerManager&) = delete;
    PlayerManager& operator=(const PlayerManager&) = delete;
    PlayerManager(PlayerManager&&) = default;
    PlayerManager& operator=(PlayerManager&&) = default;


    static PlayerManager& GetInstance()
    {
        static PlayerManager instance;  // thread-safe singleton instance
        return instance;
    }

    // Add public methods for managing players here

    void AddPlayer(const std::shared_ptr<dae::GameObject>& player)
    {
	    m_Players.push_back(player);
    }
    void RemovePlayer(const std::shared_ptr<dae::GameObject>& player)
    {
        m_Players.erase(std::remove(m_Players.begin(), m_Players.end(), player), m_Players.end());
    }
    std::vector<std::shared_ptr<dae::GameObject>> GetPlayers() { return m_Players; }

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

private:
    PlayerManager() = default;

    std::vector<std::shared_ptr<dae::GameObject>> m_Players;

    GameMode m_GameMode{ SinglePlayer };
    std::vector<glm::vec2> m_SpawnPositions;
};

