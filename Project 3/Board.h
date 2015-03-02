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
	board();
	~board();
	board(int);

	void clear(int i, int j);
	void setCell(int row, int col, int v);
	void initialize(ifstream &fin);
	
	void print();
	void printConflicts();
	bool isBlank(int, int);
	ValueType getCell(int, int);	
	int squareNumber(int i, int j);
	bool checkSolved(board b);

	bool checkConflicts(int i, int j, int v);
	bool checkVertConflict(int i, int j, int v);
	bool checkHorzConflict(int i, int j, int v);
	bool checkSquareConflict(int i, int j, int v);

private:
	// The following matrices go from 1 to BoardSize in each
	// dimension.  I.e. they are each (BoardSize+1) X (BoardSize+1)
	matrix<ValueType> value;
	vector<vector<int>> conflicts;

	vector<bool> vertConflicts;
	vector<bool> horzConflicts;
	vector<bool> squareConflicts;

	// Conflict matrices 
	matrix<bool> conflictRow;
	matrix<bool> conflictCol;
	matrix<bool> conflictSq;
};
