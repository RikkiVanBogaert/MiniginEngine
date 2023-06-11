#pragma once
#include "Observers.h"

#include <vector>
#include <memory>


namespace dae
{
    class Subject final
	{
    public:
        void Attach(const std::shared_ptr<Observer>& observer)
    	{
            m_pObservers.push_back(observer);
        }

        void Detach(const std::shared_ptr<Observer>& observer)
    	{
            for (auto it = m_pObservers.begin(); it != m_pObservers.end(); ++it) 
            {
                if (*it == observer) 
                {
                    m_pObservers.erase(it);
                    break;
                }
            }
        }

        void Notify(const std::shared_ptr<ObserverEvent>& event) const
    	{
            for (const std::shared_ptr<Observer>& observer : m_pObservers) 
            {
                observer->OnNotify(event);
            }
        }

    private:
        std::vector<std::shared_ptr<Observer>> m_pObservers;

    };

}
