#ifndef __MOTORCYCLE_H_
#define __MOTORCYCLE_H_


#include "..\Defs.h"
#include "Order.h"

#pragma once
class Motorcycle	
{
	int id;
	int OrdID;
	ORD_TYPE type;		//for each order type there is a corresponding motorcycle type 
	double speed;		//meters it can move in one clock tick (in one timestep)
	REGION	region;		//region of the motorcycle
	STATUS	status;		//idle or in-service
	int HP;				// health point
	int FT;
	double ST;
	bool wasInTraffic;
	int repaired;

public:
	Motorcycle();
	Motorcycle(int i, ORD_TYPE t, double s, REGION r, STATUS ss , int hp, int Id);
	bool operator>(Motorcycle& m2);
	virtual ~Motorcycle();
	void Assign(Order* & ord, int timeStep);
	int getFT() const;
	double getST() const;
	void deAssign();
	ORD_TYPE getOrdType() const;
	bool getWasInTraffic() const;
	int getHP() const;
	void Repair(int timeStep);
	int getRepairTime() const;
	void setID(int Id);
	int getID()const;
	ORD_TYPE getType() const;
private:
	bool RandomBool();
};

#endif