#pragma once

#include <iostream>
#include <limits.h>
#include "d_matrix.h"
#include "d_except.h"
#include "Constants.h"
#include <list>
#include <fstream>

using namespace std; 

class board
	// Stores the entire Sudoku board
{
public:
	board(int);
	void clear();
	void initialize(ifstream &fin);
	void print();
	bool isBlank(int, int);
	ValueType getCell(int, int);

private:

	// The following matrices go from 1 to BoardSize in each
	// dimension.  I.e. they are each (BoardSize+1) X (BoardSize+1)

	matrix<ValueType> value;
};
