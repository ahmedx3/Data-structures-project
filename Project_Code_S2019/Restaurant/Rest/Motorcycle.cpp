#include "Motorcycle.h"


Motorcycle::Motorcycle()
{
}

Motorcycle::Motorcycle(int i, ORD_TYPE t, int s, REGION r, STATUS ss)
{
	ID = i;
	type = t;
	speed = s;
	region = r;
	status = ss;
}

bool Motorcycle::operator>(Motorcycle & m2)
{
	return speed > m2.speed;
}


Motorcycle::~Motorcycle()
{
}
