#include "AudioService.h"

#include <SDL_mixer.h>
#include <queue>
#include <vector>

class SDLSoundSystem::SDLSoundSystemImpl
{
public:
    SDLSoundSystemImpl()
    {
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        {
            std::cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << '\n';
            return;
        }

        m_SoundThread = std::thread(&SDLSoundSystemImpl::SoundThreadFunction, this);
    }

    ~SDLSoundSystemImpl()
    {
        StopSoundThread();
    }

    void AddSound(const std::string& soundName)
    {
        m_AudioClips.emplace_back(std::shared_ptr<Mix_Chunk>(Mix_LoadWAV(soundName.c_str()), Mix_FreeChunk));

        if (!m_AudioClips[m_AudioClips.size() - 1])
        {
            std::cout << "Failed to load sound effect: " << soundName << '\n';
        }
    }

    void Play(const soundId id, const int volume)
    {
        if (id >= m_AudioClips.size())
            return;

        {
            std::lock_guard<std::mutex> lock(m_QueueMutex);
            m_SoundQueue.push({ id, volume });
        }

        m_QueueCondition.notify_one();
    }

    void MuteUnmuteSound()
    {
        m_IsMuted = !m_IsMuted;
    }

private:
    std::vector<std::shared_ptr<Mix_Chunk>> m_AudioClips;
    bool m_IsMuted{};
    bool m_QuitFlag{};
    std::queue<std::pair<int, int>> m_SoundQueue;
    std::thread m_SoundThread;
    std::mutex m_QueueMutex;
    std::condition_variable m_QueueCondition;

    void SoundThreadFunction()
    {
        while (true)
        {
            std::unique_lock<std::mutex> lock(m_QueueMutex);
            m_QueueCondition.wait(lock, [this] { return !m_SoundQueue.empty() || m_QuitFlag; });

            if (m_QuitFlag)
            {
                break;
            }

            const int id = m_SoundQueue.front().first;
            const int volume = m_SoundQueue.front().second;
            m_SoundQueue.pop();

            lock.unlock();

            if (!m_IsMuted)
            {
                // Play the sound with the given ID
                Mix_Volume(-1, volume);
                Mix_PlayChannel(-1, m_AudioClips[id].get(), 0); // Third argument is the number of loops
            }

            // Sleep for a short duration to avoid busy-waiting
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }

    void StopSoundThread()
    {
        {
            std::lock_guard<std::mutex> lock(m_QueueMutex);
            m_QuitFlag = true;
        }

        m_QueueCondition.notify_one();

        if (m_SoundThread.joinable())
        {
            m_SoundThread.join();
        }
    }


};


SDLSoundSystem::SDLSoundSystem()
{
    m_pImpl = std::make_unique<SDLSoundSystemImpl>();
}

SDLSoundSystem::~SDLSoundSystem()
{
    m_pImpl.release();
}

void SDLSoundSystem::AddSound(const std::string& soundName)
{
    m_pImpl->AddSound(soundName);
}

void SDLSoundSystem::Play(const soundId id, const int volume)
{
    m_pImpl->Play(id, volume);
}

void SDLSoundSystem::MuteUnmuteSound()
{
    m_pImpl->MuteUnmuteSound();
}
