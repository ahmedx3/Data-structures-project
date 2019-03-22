#include "ArrivalEvent.h"
#include "..\Rest\Restaurant.h"


ArrivalEvent::ArrivalEvent(int eTime, int oID, ORD_TYPE oType, REGION reg):Event(eTime, oID)
{
	OrdType = oType;
	OrdRegion = reg;
}

ArrivalEvent::ArrivalEvent(int eTime, int oID, ORD_TYPE oType, REGION reg, double money, int distance): Event(eTime, oID)
{
	OrdDistance = distance;
	OrdType = oType;
	OrdRegion = reg;
	OrdMoney = money;
}

void ArrivalEvent::Execute(Restaurant* pRest)
{
	//This function should create an order and fills its data 
	// Then adds it to normal, frozen, or VIP order lists that you will create in phase1

	Order* pOrd = new Order(OrderID, OrdType, OrdRegion);

	if (OrdType == TYPE_NRM) {
		if (OrdRegion == A_REG)
			pRest->addToNormalQueueRegionA(pOrd);
		else if (OrdRegion == B_REG)
			pRest->addToNormalQueueRegionB(pOrd);
		else if (OrdRegion == C_REG)
			pRest->addToNormalQueueRegionC(pOrd);
		else
			pRest->addToNormalQueueRegionD(pOrd);
	}
	else if (OrdType == TYPE_FROZ) {
		if (OrdRegion == A_REG)
			pRest->addToFrozenQueueRegionA(pOrd);
		else if (OrdRegion == B_REG)
			pRest->addToFrozenQueueRegionB(pOrd);
		else if (OrdRegion == C_REG)
			pRest->addToFrozenQueueRegionC(pOrd);
		else
			pRest->addToFrozenQueueRegionD(pOrd);
	}
	else {
		if (OrdRegion == A_REG)
			pRest->addToVIPQueueRegionA(pOrd);
		else if (OrdRegion == B_REG)
			pRest->addToVIPQueueRegionB(pOrd);
		else if (OrdRegion == C_REG)
			pRest->addToVIPQueueRegionC(pOrd);
		else
			pRest->addToVIPQueueRegionD(pOrd);
	}
}
