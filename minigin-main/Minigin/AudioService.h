#pragma once
#include <iostream>

class AudioImpl;

class Audio final
{
public:
	Audio();
	virtual ~Audio();
	void addSound(const std::string& soundName);
	void playSound(int soundID);
	void stopSound(int soundID);
	void stopAllSounds();

private:
	std::unique_ptr<AudioImpl> impl_;
};

class Locator final
{
public:
	static void initialize() {}

	static Audio& getAudio() { return *service_; }

	static void provide(std::shared_ptr<Audio> service)
	{
		service_ = service;
	}

private:
	static std::shared_ptr<Audio> service_;
};