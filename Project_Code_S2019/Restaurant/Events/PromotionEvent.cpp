#include "PromotionEvent.h"
#include "..\Rest\Restaurant.h"


PromotionEvent::PromotionEvent(int eTime, int oID, double Money): Event(eTime, oID)
{
	extraMoney = Money;
}


PromotionEvent::~PromotionEvent()
{
}

void PromotionEvent::Execute(Restaurant*pRest)
{
	pRest->promoteToVIP(OrderID, extraMoney);
}
