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
		virtual void Update(ObserverEvent event) = 0;
	};

}
