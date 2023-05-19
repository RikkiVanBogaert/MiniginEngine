#pragma once
#include "Event.h"
#include "AudioService.h"

//class SoundEvent final : public Event
//{
//public:
//    SoundEvent(int value, int sound_id)
//        : Event(value), sound_id_(sound_id)
//    {}
//    SoundEvent() = default;
//
//    virtual void execute() override
//    {
//        Locator::getAudio().playSound(sound_id_);
//        std::cout << "PLAY SOUND " << sound_id_ << '\n';
//    }
//
//private:
//    int sound_id_;
//};

