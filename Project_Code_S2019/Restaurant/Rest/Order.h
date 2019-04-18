#ifndef __ORDER_H_
#define __ORDER_H_

#include "..\Defs.h"

#include <iostream>		//for testing the output
using namespace std;	//for testin the output

class Order
{

protected:
	int ID;								//Each order has a unique ID (from 1 --> 999 )
	ORD_TYPE type;						//order type: Normal, Frozen, VIP
	REGION Region;						//Region of this order
	int Distance;						//The distance (in meters) between the order location and the resturant 
	double totalMoney;					//Total order money
	int ArrTime, ServTime, FinishTime, WaitingTime;	//arrival, service start, and finish times
	double Priority;					//Priority of the order (ony for VIP orders)
	//
	// TODO: Add More Data Members As Needed
	//

public:
	Order(int ID, ORD_TYPE r_Type, REGION r_region, int a_t, int d, double money);
	Order();
	virtual ~Order();


	void setArrTime(const int& a_t);
	void setServTime(const int& s_t);
	void setFinishTime(const int& f_t);

	void SetID(const int& id);
	int GetID();

	void setMoney(double money);
	double getMoney()const;


	void SetType(const ORD_TYPE& r_Type);
	ORD_TYPE GetType() const;

	void SetRegion(const REGION& r_region);
	REGION GetRegion() const;

	void SetDistance(int d);
	int GetDistance() const;

	void setPriority(); //only for VIP orders
	double getPriority() const;	 //only for VIP orders

	bool operator >(const Order& o) const;	// compares the priority of two orders
	bool operator ==(const int id) const;	// compares the ID of an order with a given ID
	//
	// TODO: Add More Member Functions As Needed
	//
	void setWaitingTime();
};

#endif