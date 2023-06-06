#include "SDL_mixer.h"
#include <iostream>

#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>


using sound_id = unsigned short;
class SoundSystem
{
public:
	virtual ~SoundSystem() = default;
	virtual void Play(const sound_id id, const int volume) = 0;
	virtual void AddSound(const std::string& soundName) = 0;
	virtual void MuteUnmuteSound() = 0;
};

class SDLSoundSystem final : public SoundSystem
{
public:
    SDLSoundSystem()
    {
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        {
            std::cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << '\n';
            return;
        }

        m_SoundThread = std::thread(&SDLSoundSystem::SoundThreadFunction, this);
    }

    ~SDLSoundSystem() override
    {
        StopSoundThread();
    }

    void AddSound(const std::string& soundName) override
    {
        m_AudioClips.emplace_back(std::shared_ptr<Mix_Chunk>(Mix_LoadWAV(soundName.c_str()), Mix_FreeChunk));

        if (!m_AudioClips[m_AudioClips.size() - 1])
        {
            std::cout << "Failed to load sound effect: " << soundName << '\n';
        }
    }

    void Play(const sound_id id, const int volume) override
    {
        if (id >= m_AudioClips.size())
            return;

        {
            std::lock_guard<std::mutex> lock(m_QueueMutex);
            m_SoundQueue.push({ id, volume });
        }

        m_QueueCondition.notify_one();
    }

    void MuteUnmuteSound() override
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

            int id = m_SoundQueue.front().first;
            int volume = m_SoundQueue.front().second;
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

class LoggingSoundSystem final : public SoundSystem
{
	std::unique_ptr<SDLSoundSystem> RealSs;
public:
	LoggingSoundSystem(std::unique_ptr<SDLSoundSystem>&& ss) : RealSs(std::move(ss)) {}
	virtual ~LoggingSoundSystem() = default;

	void Play(const sound_id id, const int volume = 1) override
	{
		RealSs->Play(id, volume);
		std::cout << "playing " << id << " at volume " << volume << std::endl;
	}

	void AddSound(const std::string& soundName) override
	{
		RealSs->AddSound(soundName);
		std::cout << "adding sound: " << soundName << std::endl;
	}

	void MuteUnmuteSound() override
	{
		RealSs->MuteUnmuteSound();
		std::cout << "muting/unmuting sound\n";
	}
};

class NullSoundSystem final : public SoundSystem
{
	void Play(const sound_id, const int) override {}
	void AddSound(const std::string& ) override {}
	void MuteUnmuteSound() override {}
};

class Servicelocator final
{
	static std::unique_ptr<SoundSystem> SsInstance;
public:
	static SoundSystem& GetSoundSystem() { return *SsInstance; }
	static void RegisterSoundSystem(std::unique_ptr<SoundSystem>&& ss)
	{
		SsInstance = ss == nullptr ? std::make_unique<NullSoundSystem>() : std::move(ss);
	}
};