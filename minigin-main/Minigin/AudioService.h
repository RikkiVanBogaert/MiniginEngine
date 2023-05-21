#include "SDL_mixer.h"
#include <iostream>

using sound_id = unsigned short;
class sound_system
{
public:
	virtual ~sound_system() = default;
	virtual void play(const sound_id id, const int volume) = 0;
	virtual void addSound(const std::string& soundName) = 0;
	virtual void MuteUnmuteSound() = 0;
};

class sdl_sound_system final : public sound_system
{
public:
	sdl_sound_system()
	{
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			std::cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << '\n';
			return;
		}
	}
	~sdl_sound_system()
	{
		Mix_Quit();
	}

	void addSound(const std::string& soundName)
	{
		m_AudioClips.emplace_back(std::shared_ptr<Mix_Chunk>(Mix_LoadWAV(soundName.c_str()), Mix_FreeChunk));

		if (!m_AudioClips[m_AudioClips.size() - 1]) 
		{
			std::cout << "Failed to load sound effect: " << soundName << '\n';
		}
	}

	void play(const sound_id id, const int volume)
	{
		if (m_IsMuted) return;

		if (id >= m_AudioClips.size()) return;

		auto audioclip = m_AudioClips[id];
		Mix_Volume(-1, volume);
		Mix_PlayChannel(-1, audioclip.get(), 0); //third argument is amount of loops
	}

	void MuteUnmuteSound()
	{
		m_IsMuted = !m_IsMuted;
	}

private:
	std::vector<std::shared_ptr<Mix_Chunk>> m_AudioClips;
	bool m_IsMuted{};
};

class logging_sound_system final : public sound_system
{
	std::unique_ptr<sdl_sound_system> _real_ss;
public:
	logging_sound_system(std::unique_ptr<sdl_sound_system>&& ss) : _real_ss(std::move(ss)) {}
	virtual ~logging_sound_system() = default;

	void play(const sound_id id, const int volume = 1) override
	{
		_real_ss->play(id, volume);
		std::cout << "playing " << id << " at volume " << volume << std::endl;
	}

	void addSound(const std::string& soundName) override
	{
		_real_ss->addSound(soundName);
		std::cout << "adding sound: " << soundName << std::endl;
	}

	void MuteUnmuteSound() override
	{
		_real_ss->MuteUnmuteSound();
		std::cout << "muting/unmuting sound\n";
	}
};

class null_sound_system final : public sound_system
{
	void play(const sound_id, const int) override {}
	void addSound(const std::string& ) override {}
	void MuteUnmuteSound() override {};
};

class servicelocator final
{
	static std::unique_ptr<sound_system> _ss_instance;
public:
	static sound_system& get_sound_system() { return *_ss_instance; }
	static void register_sound_system(std::unique_ptr<sound_system>&& ss)
	{
		_ss_instance = ss == nullptr ? std::make_unique<null_sound_system>() : std::move(ss);
	}
};