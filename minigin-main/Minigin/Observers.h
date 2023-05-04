#pragma once
#include "Event.h"
#include <string>


namespace dae
{
	class GameObject;


	class Observer
	{
	public:
		virtual ~Observer() {}

		virtual void OnNotify(Event event, GameObject* gameObject) = 0;

	};

	class UI final : public Observer
	{
	public:
		virtual void OnNotify(Event event, GameObject* gameObject);

	private:

		void UpdateUI(GameObject* owner, const std::string& type); //change this to enum maybe
	};

}