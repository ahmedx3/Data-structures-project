#pragma once

#include "Event.h"

class CancelationEvent: public Event
{
public:
	CancelationEvent(int eTime, int oID);
	~CancelationEvent();

	virtual void Execute(Restaurant *pRest);
};

