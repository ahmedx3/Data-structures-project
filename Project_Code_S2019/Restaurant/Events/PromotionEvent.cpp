#include "PromotionEvent.h"



PromotionEvent::PromotionEvent(int eTime, int oID, double Money): Event(eTime, oID)
{
	extraMoney = Money;
}


PromotionEvent::~PromotionEvent()
{
}

void PromotionEvent::Execute(Restaurant * pRest)
{
}
