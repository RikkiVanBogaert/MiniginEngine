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
		soundEffects_.emplace_back(Mix_LoadWAV(soundName.c_str()));

		if(!soundEffects_[soundEffects_.size()-1])
		{
			std::cout << "Failed to load sound effect: " << soundName << '\n';
		}
	}

	virtual void playSound(int soundID)
	{
		Mix_PlayChannel(-1, soundEffects_[soundID], 0);
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
	std::vector<Mix_Chunk*> soundEffects_;
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
	static void initialize() { service_ = &nullService_; }

	static Audio& getAudio() { return *service_; }

	static void provide(Audio* service)
	{
		if (service == nullptr)
		{
			// Revert to null service.
			service_ = &nullService_;
		}
		else
		{
			service_ = service;
		}
	}

private:
	static Audio* service_;
	static NullAudio nullService_;
};

Audio* Locator::service_;
NullAudio Locator::nullService_;