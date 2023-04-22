#pragma once
#include "Event.h"

#include <vector>
#include <iostream>


class Observer;
class GameObject;

class Subject
{
public:
	Subject(GameObject* owner);
	~Subject() = default;

	void AddObserver(std::shared_ptr<Observer> observer);
	void RemoveObserver(std::shared_ptr<Observer> observer);

	void NotifyObservers(Event event);

private:
	GameObject* m_pOwner;
	std::vector<std::shared_ptr<Observer>> m_pObservers;

};

