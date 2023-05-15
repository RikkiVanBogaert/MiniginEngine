#pragma once
#include "ObserverEvent.h"
#include <string>


namespace dae
{
	class GameObject;


	class Observer
	{
	public:
		virtual ~Observer() {}

		virtual void OnNotify(ObserverEvent event, GameObject* gameObject) = 0;

	};

	class UI final : public Observer
	{
	public:
		virtual void OnNotify(ObserverEvent event, GameObject* gameObject);

	private:

		void UpdateUI(GameObject* owner, const std::string& type); //change this to enum maybe
	};

}