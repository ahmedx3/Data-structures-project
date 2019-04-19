#ifndef __PROMOTION_EVENT_H_
#define __PROMOTION_EVENT_H_
#include "Event.h"

class PromotionEvent: public Event
{
	double extraMoney;

public:
	PromotionEvent(int eTime, int oID, double Money);
	~PromotionEvent();

	virtual void Execute(Restaurant *pRest);
};

#endif //!__PROMOTION_EVENT_H_