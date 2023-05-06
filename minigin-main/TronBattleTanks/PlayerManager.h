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
    static PlayerManager& GetInstance()
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


    enum GameMode
    {
        SinglePlayer,
        Coop,
        Versus
    };
    void SwitchGameMode();
    GameMode GetGameMode() const { return m_GameMode; }

private:
    PlayerManager() {}  // private constructor to prevent direct instantiation
    PlayerManager(const PlayerManager&) = delete;  // delete copy constructor
    PlayerManager& operator=(const PlayerManager&) = delete;  // delete copy assignment operator

    std::vector<std::shared_ptr<dae::GameObject>> m_Players;

    GameMode m_GameMode{ GameMode::SinglePlayer };
};

