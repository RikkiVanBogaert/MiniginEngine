#include "SDL_mixer.h"
#include <iostream>

using sound_id = unsigned short;
class sound_system
{
public:
	virtual ~sound_system() = default;
	virtual void play(const sound_id id, const float volume) = 0;
	virtual void addSound(const std::string& soundName) = 0;
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
		audioClips.emplace_back(std::shared_ptr<Mix_Chunk>(Mix_LoadWAV(soundName.c_str()), Mix_FreeChunk));

		if (!audioClips[audioClips.size() - 1]) 
		{
			std::cout << "Failed to load sound effect: " << soundName << '\n';
		}
	}

	void play(const sound_id id, const float )
	{
		if (id >= audioClips.size()) return;

		auto audioclip = audioClips[id];
		//audioclip->set_volume(volume);
		Mix_PlayChannel(-1, audioclip.get(), 0);
	}

private:
	std::vector<std::shared_ptr<Mix_Chunk>> audioClips;
};

class logging_sound_system final : public sound_system
{
	std::unique_ptr<sdl_sound_system> _real_ss;
public:
	logging_sound_system(std::unique_ptr<sdl_sound_system>&& ss) : _real_ss(std::move(ss)) {}
	virtual ~logging_sound_system() = default;

	void play(const sound_id id, const float volume = 1) override
	{
		_real_ss->play(id, volume);
		std::cout << "playing " << id << " at volume " << volume << std::endl;
	}

	void addSound(const std::string& soundName) override
	{
		_real_ss->addSound(soundName);
		std::cout << "adding sound: " << soundName << std::endl;
	}
};

class null_sound_system final : public sound_system
{
	void play(const sound_id, const float) override {}
	void addSound(const std::string& ) override {}
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