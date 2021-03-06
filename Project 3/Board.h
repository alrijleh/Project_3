/*
Board.h
Contains funcitonality for the board class

Fouad Al-Rijleh, Rachel Rudolph
*/
#pragma once

#include <iostream>
#include <limits.h>
#include "d_matrix.h"
#include "d_except.h"
#include "Constants.h"
#include "Cell.h"
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

	void clearCell(int i, int j);
	void setCell(int row, int col, int v);
	void initialize(ifstream &fin);
	void clearBoard();
	
	void print();
	int getCounter();
	bool isBlank(int, int);
	ValueType getCell(int, int);	
	int squareNumber(int i, int j);
	bool checkSolved();

	void solve();
	int board::countPossibleValues(int i, int j);
	vector<int> board::findMinimumLocation(vector<Cell> cellVector);
	vector<int> findNextBlank();
	vector<int> findBestBlank();

	void updateVectors(int i, int j, int v);

	bool checkConflicts(int i, int j, int v);
	void printConflicts();

private:
	// The following matrices go from 1 to BoardSize in each
	// dimension.  I.e. they are each (BoardSize+1) X (BoardSize+1)

	matrix<ValueType> value;
	int counter;

	//counters
	matrix<bool> inRow;
	matrix<bool> inCol;
	matrix<bool> inSquare;
};
