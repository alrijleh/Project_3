#include "Cell.h"

void Cell::setLocation(int i, int j)
{
	location = { i, j };
}

void Cell::setLocation(vector<int> newLocation)
{
	location = newLocation;
}

vector<int> Cell::getLocation()
{
	return location;
}

void Cell::setValue(int newValue)
{
	value = newValue; 
}

int Cell::getValue()
{
	return value;
}

Cell::Cell()
{
}


Cell::~Cell()
{
}
