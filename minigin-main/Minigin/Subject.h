#pragma once
#include "ObserverEvent.h"

#include <vector>
#include <iostream>
#include <memory>

#include "Observers.h"

namespace dae
{
    // Subject class
    class Subject final
	{
    private:
        std::vector<std::shared_ptr<Observer>> observers;

    public:
        void attach(std::shared_ptr<Observer> observer)
    	{
            observers.push_back(observer);
        }

        void detach(std::shared_ptr<Observer> observer)
    	{
            for (auto it = observers.begin(); it != observers.end(); ++it) {
                if (*it == observer) {
                    observers.erase(it);
                    break;
                }
            }
        }

        void Notify(ObserverEvent event)
    	{
            for (std::shared_ptr<Observer> observer : observers) 
            {
                observer->Update(event);
            }
        }
    };

}
