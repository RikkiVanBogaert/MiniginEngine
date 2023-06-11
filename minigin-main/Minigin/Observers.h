#pragma once

#include "ObserverEvent.h"

#include <memory>

namespace dae
{
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

		virtual void Update(std::shared_ptr<ObserverEvent> event) = 0;
	};

}
