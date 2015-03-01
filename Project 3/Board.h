#pragma once

#include <iostream>
#include <limits.h>
#include "d_matrix.h"
#include "d_except.h"
#include "Constants.h"
#include <list>
#include <fstream>
#include <vector>

using namespace std; 

class board
	// Stores the entire Sudoku board
{
public:
	board(int);
	void clear(int i, int j);
	void setCell(int row, int col, int v);
	void initialize(ifstream &fin);
	bool checkConflicts(int i, int j, int v);
	void print();
	void printConflicts();
	bool isBlank(int, int);
	ValueType getCell(int, int);	
	int squareNumber(int i, int j);
	bool checkSolved(board b);

private:
	// The following matrices go from 1 to BoardSize in each
	// dimension.  I.e. they are each (BoardSize+1) X (BoardSize+1)
	matrix<ValueType> value;

	// Conflict matrices 
	matrix<bool> conflictRow;
	matrix<bool> conflictCol;
	matrix<bool> conflictSq;
};
