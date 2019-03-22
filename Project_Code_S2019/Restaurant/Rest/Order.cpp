#include "Order.h"

Order::Order(int id, ORD_TYPE r_Type, REGION r_region)
{
	ID = (id>0&&id<1000)?id:0;	//1<ID<999
	type = r_Type;
	Region = r_region;
}
Order::Order() {
	//To avoid errors if a node is instantiated without assigning a value to its item of type Order
}
Order::~Order()
{
}

void Order::SetID(const int& id)
{
	ID = (id > 0 && id < 1000) ? id : 0;
}

int Order::GetID()
{
	return ID;
}

void Order::SetRegion(const REGION & r_region)
{
	Region = r_region;
}


void Order::SetType(const ORD_TYPE & r_Type)
{
	type = r_Type;
}


int Order::GetType() const
{
	return type;
}

REGION Order::GetRegion() const
{
	return Region;
}

void Order::SetDistance(int d)
{
	Distance = d>0?d:0;
}

int Order::GetDistance() const
{
	return Distance;
}

void Order::setPriority(const double pr)
{
	Priority =(pr > 0)?pr:0;
}

double Order::getPriority() const
{
	return Priority;
}

bool Order::operator >(const Order& o) const
{
	if (Priority > o.Priority)
	{
		return true;
	}
	return false;
}

bool Order::operator==(const int id) const
{
	if (ID == id)
	{
		return true;
	}
	return false;
}


	/*---------------------------------------------for testing only------------------------------------------*/

ostream& operator <<(ostream& o, Order& ord) {
	o << "order of id:" << ord.GetID() << " and type: " << ord.GetType() << " and region: " << ord.GetRegion() << endl;
	return o;
}
