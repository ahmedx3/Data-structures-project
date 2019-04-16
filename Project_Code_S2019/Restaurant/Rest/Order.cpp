#include "Order.h"

Order::Order(int id, ORD_TYPE r_Type, REGION r_region, int a_t, int d, double money)
{
	SetID(id);	//1<ID<999
	SetType(r_Type);
	SetRegion(r_region);
	setArrTime(a_t);
	SetDistance(d);
	setMoney(money);
	if (r_Type = TYPE_VIP)
	{
		setPriority();
	}
	else
	{
		Priority = -1;		//default value for non VIP orders
	}
}
Order::Order() {
	//To avoid errors if a node is instantiated without assigning a value to its item of type Order
}
Order::~Order()
{
}

void Order::setArrTime(const int & a_t)
{
	ArrTime =( a_t > 0)?a_t:0;
}

void Order::setServTime(const int & s_t)
{
	ServTime = (s_t > 0) ? s_t : 0;
}

void Order::setFinishTime(const int & f_t)
{
	FinishTime = (f_t > 0) ? f_t : 0;
}

void Order::SetID(const int& id)
{
	ID = (id > 0 && id < 1000) ? id : 0;
}

int Order::GetID()
{
	return ID;
}

void Order::setMoney(double money)
{
	totalMoney = (money > 0) ? money : 0;
}

double Order::getMoney() const
{
	return totalMoney;
}

void Order::SetRegion(const REGION & r_region)
{
	Region = r_region;
}


void Order::SetType(const ORD_TYPE & r_Type)
{
	type = r_Type;
}


ORD_TYPE Order::GetType() const
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

void Order::setPriority()
{
	Priority = (float)totalMoney*200/(ArrTime * Distance);
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
