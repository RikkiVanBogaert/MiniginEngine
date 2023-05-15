#pragma once
#include "Event.h"

namespace dae
{
	class PointsCp;
	class GameObject;
}

class UpdateCounterEvent final : public Event
{
public:
    UpdateCounterEvent(int value, dae::GameObject* gameObject, int addedCounterValue)
        : Event(value), m_AddedCounterValue(addedCounterValue)
    {
        FindCounter(gameObject);
    }
    UpdateCounterEvent() = default;

    virtual void execute() override;

private:
    dae::PointsCp* m_pPointCounter{};

    int m_AddedCounterValue{};

    void FindCounter(dae::GameObject* gameObject);
};



