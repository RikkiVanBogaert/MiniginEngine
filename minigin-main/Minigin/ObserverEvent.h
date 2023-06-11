#pragma once

class ObserverEvent
{
public:
	virtual ~ObserverEvent() = default;
};

//must define a virtual function otherwise dynamic_cast not possible


