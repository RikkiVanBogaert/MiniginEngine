#pragma once
#include <iostream>
#include "AudioService.h"

class SoundEvent {
public:
    SoundEvent(int value, int sound_id)
        : value_(value), sound_id_(sound_id)
        {}
    SoundEvent() = default;

    virtual void execute()
	{
        Locator::getAudio().playSound(sound_id_);
        //std::cout << "SoundEvent: " << value_ << std::endl;
    }

private:
    int value_;
    int sound_id_;
};
