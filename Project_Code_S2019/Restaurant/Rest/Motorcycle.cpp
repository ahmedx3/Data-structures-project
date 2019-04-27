#include "Motorcycle.h"
#include "Math.h"
#include <ctime>

const int REST_TIME = 3;
const int REPAIR_TIME = 4;

Motorcycle::Motorcycle()
{
	wasInTraffic = false;
	FT = -999;
	repaired = -999;
}

Motorcycle::Motorcycle(int i, ORD_TYPE t, double s, REGION r, STATUS ss , int hp)
{
	ID = i;
	type = t;
	speed = s;
	region = r;
	status = ss;
	HP = hp;
	wasInTraffic = false;
	FT = -999;
	repaired = -999;
}

bool Motorcycle::operator>(Motorcycle & m2)
{
	return FT < m2.FT;
}


Motorcycle::~Motorcycle()
{
	
}

void Motorcycle::Assign(Order* & ord, int timeStep)
{
	ID = ord->GetID();
	status = SERV;

	if (wasInTraffic && FT > (timeStep - REST_TIME))
		HP -= 25;

	wasInTraffic = RandomBool();

	int traffic;

	if (wasInTraffic)
		traffic = 5;
	else
		traffic = 0;


	FT = timeStep + (2 * ceil(ord->GetDistance() / speed)) + traffic;
	ST = ceil(ord->GetDistance() / speed) + traffic;
}

int Motorcycle::getFT() const
{
	return FT;
}

double Motorcycle::getST() const
{
	return ST;
}

void Motorcycle::deAssign() {
	ID = -1;
	status = IDLE;
}

ORD_TYPE Motorcycle::getOrdType() const
{
	return type;
}

bool Motorcycle::getWasInTraffic() const
{
	return wasInTraffic;
}

int Motorcycle::getHP() const
{
	return HP;
}

void Motorcycle::Repair(int timeStep) {
	deAssign();
	wasInTraffic = false;
	FT = -999;
	repaired = timeStep + REPAIR_TIME;
	HP = 100;
}

int Motorcycle::getRepairTime() const
{
	return repaired;
}

bool Motorcycle::RandomBool() {

	srand(((unsigned)time(0)));

	if (rand() % 2)
		return true;
	else
		return false;
}