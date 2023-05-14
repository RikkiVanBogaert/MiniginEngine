#pragma once
#include <iostream>
#include "AudioService.h"

class MyEvent {
public:
    MyEvent(int value, int sound_id)
        : value_(value), sound_id_(sound_id)
        {}
    MyEvent() = default;

    virtual void execute()
	{
        Locator::getAudio().playSound(sound_id_);
        std::cout << "MyEvent: " << value_ << std::endl;
    }

private:
    int value_;
    int sound_id_;
};
