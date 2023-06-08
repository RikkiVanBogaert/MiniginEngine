#pragma once
#include "ObserverEvent.h"

class LivesCp;

namespace dae
{
	class UILivesCp;
	class Subject;

	class Observer
	{
	public:
		Observer() = default;
		virtual ~Observer() = default;

		Observer(const Observer& other) = delete;
		Observer(Observer&& other) = delete;
		Observer& operator=(const Observer& other) = delete;
		Observer& operator=(Observer&& other) = delete;

		virtual void Update(ObserverEvent event) = 0;
	};

}
