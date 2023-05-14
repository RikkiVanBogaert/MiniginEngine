#include "AudioService.h"
#include <iostream>
#include <vector>
#include "SDL_mixer.h"

class AudioImpl
{
public:
    AudioImpl()
	{
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) 
        {
            std::cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << '\n';
            return;
        }
    }

    ~AudioImpl()
	{
        Mix_Quit();
    }

    void addSound(const std::string& soundName)
	{
        soundEffects_.emplace_back(std::shared_ptr<Mix_Chunk>(Mix_LoadWAV(soundName.c_str()), Mix_FreeChunk));

        if (!soundEffects_[soundEffects_.size() - 1]) {
            std::cout << "Failed to load sound effect: " << soundName << '\n';
        }
    }

    void playSound(int soundID)
	{
        Mix_PlayChannel(-1, soundEffects_[soundID].get(), 0);
    }

    void stopSound(int soundID)
	{
        Mix_HaltChannel(soundID);
    }

    void stopAllSounds()
	{
        Mix_HaltChannel(-1);
    }

private:
    std::vector<std::shared_ptr<Mix_Chunk>> soundEffects_;
};

Audio::Audio() : impl_(new AudioImpl()) {}

Audio::~Audio() = default;

void Audio::addSound(const std::string& soundName)
{
    impl_->addSound(soundName);
}

void Audio::playSound(int soundID)
{
    impl_->playSound(soundID);
}

void Audio::stopSound(int soundID)
{
    impl_->stopSound(soundID);
}

void Audio::stopAllSounds()
{
    impl_->stopAllSounds();
}