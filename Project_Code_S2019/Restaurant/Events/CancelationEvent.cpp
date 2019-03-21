#include "CancelationEvent.h"
#include "..\Rest\Restaurant.h"



CancelationEvent::CancelationEvent(int eTime, int oID): Event(eTime, oID)
{
}


CancelationEvent::~CancelationEvent()
{
}

void CancelationEvent::Execute(Restaurant * pRest)
{
	pRest->cancelOrder(OrderID);
}
