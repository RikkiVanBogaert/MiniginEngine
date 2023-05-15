#pragma once
#include "ObserverEvent.h"

#include <vector>
#include <iostream>

namespace dae
{
	class Observer;
	class GameObject;

	class Subject
	{
	public:
		Subject(GameObject* owner);
		~Subject() = default;

		void AddObserver(std::shared_ptr<Observer> observer);
		void RemoveObserver(std::shared_ptr<Observer> observer);

		void NotifyObservers(ObserverEvent event);

	private:
		GameObject* m_pOwner;
		std::vector<std::shared_ptr<Observer>> m_pObservers;

	};

}