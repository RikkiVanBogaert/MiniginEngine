#pragma once
#include <memory>
#include <vector>

namespace dae
{
    class GameObject;
}

class PlayerManager
{
public:
    static PlayerManager& getInstance()
    {
        static PlayerManager instance;  // thread-safe singleton instance
        return instance;
    }

    // Add public methods for managing players here

    void AddPlayer(std::shared_ptr<dae::GameObject> player) { m_Players.push_back(player); }
    void RemovePlayer(std::shared_ptr<dae::GameObject> player)
    {
        m_Players.erase(std::remove(m_Players.begin(), m_Players.end(), player), m_Players.end());
    }


    std::vector<std::shared_ptr<dae::GameObject>> GetPlayers() { return m_Players; }

private:
    PlayerManager() {}  // private constructor to prevent direct instantiation
    PlayerManager(const PlayerManager&) = delete;  // delete copy constructor
    PlayerManager& operator=(const PlayerManager&) = delete;  // delete copy assignment operator

    std::vector<std::shared_ptr<dae::GameObject>> m_Players;
};

