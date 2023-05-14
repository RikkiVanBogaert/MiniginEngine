#pragma once
#include "SDL_mixer.h"

class Audio
{
public:
	virtual ~Audio() {}
	virtual void playSound(int soundID) = 0;
	virtual void stopSound(int soundID) = 0;
	virtual void stopAllSounds() = 0;
};

class ConsoleAudio : public Audio
{
public:
	virtual void playSound(int /*soundID*/)
	{
		// Play sound using console audio api...

	}

	virtual void stopSound(int /*soundID*/)
	{
		// Stop sound using console audio api...
	}

	virtual void stopAllSounds()
	{
		// Stop all sounds using console audio api...
	}
};

class NullAudio : public Audio
{
public:
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