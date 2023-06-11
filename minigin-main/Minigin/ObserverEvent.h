#pragma once

class ObserverEvent
{
public:
	virtual void Function() {}
};

//must define a virtual function otherwise dynamic_cast not possible


