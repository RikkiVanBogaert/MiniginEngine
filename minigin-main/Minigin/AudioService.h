#pragma once
#include <iostream>
#include <vector>

#include "SDL_mixer.h"

class Audio
{
public:
	virtual ~Audio() {}
	virtual void addSound(const std::string& soundName) = 0;
	virtual void playSound(int soundID) = 0;
	virtual void stopSound(int soundID) = 0;
	virtual void stopAllSounds() = 0;
};

class ConsoleAudio : public Audio
{
public:
	ConsoleAudio()
	{
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			std::cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << '\n';
			return;
		}
	}

	virtual ~ConsoleAudio()
	{
		Mix_Quit();
	}

	virtual void addSound(const std::string& soundName)
	{
		soundEffects_.emplace_back(std::shared_ptr<Mix_Chunk>(Mix_LoadWAV(soundName.c_str()), Mix_FreeChunk));

		if(!soundEffects_[soundEffects_.size()-1])
		{
			std::cout << "Failed to load sound effect: " << soundName << '\n';
		}
	}

	virtual void playSound(int soundID)
	{
		Mix_PlayChannel(-1, soundEffects_[soundID].get(), 0);
	}

	virtual void stopSound(int soundID)
	{
		Mix_HaltChannel(soundID);
	}

	virtual void stopAllSounds()
	{
		Mix_HaltChannel(-1);
	}

private:
	std::vector<std::shared_ptr<Mix_Chunk>> soundEffects_;
};

class NullAudio : public Audio
{
public:
	virtual void addSound(const std::string& /*soundName*/){ /* Do nothing. */ }
	virtual void playSound(int /*soundID*/) { /* Do nothing. */ }
	virtual void stopSound(int /*soundID*/) { /* Do nothing. */ }
	virtual void stopAllSounds() { /* Do nothing. */ }
};


class Locator
{
public:
	static void initialize() { service_ = std::make_shared<NullAudio>(); }

	static Audio& getAudio() { return *service_; }

	static void provide(std::shared_ptr<Audio> service)
	{
		if (!service)
		{
			// Revert to null service.
			service_ = std::make_shared<NullAudio>();
		}
		else
		{
			service_ = service;
		}
	}

private:
	static std::shared_ptr<Audio> service_;
	static NullAudio nullService_;
};