#pragma once

#include "d_matrix.h"
#include "d_except.h"
#include "Constants.h"
#include <vector>

class Cell
{
private:
	vector<int> location;
	int value;

public:
	void setLocation(int i, int j);
	void setLocation(vector<int> newLocation);
	vector<int> getLocation();

	void setValue(int newValue);
	int getValue();

	Cell();
	~Cell();
};

