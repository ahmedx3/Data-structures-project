#include "Motorcycle.h"


Motorcycle::Motorcycle()
{
}

Motorcycle::Motorcycle(int i, ORD_TYPE t, int s, REGION r, STATUS ss , int hp)
{
	ID = i;
	type = t;
	speed = s;
	region = r;
	status = ss;
	HP = hp;
}

bool Motorcycle::operator>(Motorcycle & m2)
{
	return speed > m2.speed;
}


Motorcycle::~Motorcycle()
{
}
