#pragma once

#include "Event.h"

class PromotionEvent: public Event
{
	double extraMoney;

public:
	PromotionEvent(int eTime, int oID, double Money);
	~PromotionEvent();

	virtual void Execute(Restaurant *pRest);
};

