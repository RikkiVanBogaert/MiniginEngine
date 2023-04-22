#include "Subject.h"
#include "Observers.h"

Subject::Subject(GameObject* owner)
{
    m_pOwner = owner;
}

void Subject::AddObserver(std::shared_ptr<Observer> observer)
{
    m_pObservers.push_back(observer);
}

void Subject::RemoveObserver(std::shared_ptr<Observer> observer)
{
    m_pObservers.erase(std::remove(m_pObservers.begin(), m_pObservers.end(), observer), m_pObservers.end());
}

void Subject::NotifyObservers(Event event)
{
    for (const auto& observer : m_pObservers)
    {
        observer->OnNotify(event, m_pOwner);
    }
}
