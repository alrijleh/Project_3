#include "Board.h"

board::board(int sqSize): value(BoardSize + 1, BoardSize + 1)
// Board constructor
{
	conflictRow.resize(MaxValue, MaxValue);
	conflictCol.resize(MaxValue, MaxValue);
	conflictSq.resize(MaxValue, MaxValue);

	//Initialize conflict info
	for (int i = 0; i < MaxValue; i++)
	{
		for (int j = 0; j < MaxValue; j++)
		{
			conflictRow[i][j] = false;
			conflictCol[i][j] = false;
			conflictSq[i][j] = false;
		}
	}
}

int board::squareNumber(int i, int j)
// Return the square number of cell i,j (counting from left to right,
// top to bottom.  Note that i and j each go from 1 to BoardSize
{
	// Note that (int) i/SquareSize and (int) j/SquareSize are the x-y
	// coordinates of the square that i,j is in.  

	return SquareSize * ((i - 1) / SquareSize) + (j - 1) / SquareSize + 1;
}

void board::clear()
{
}

void board::setCell(int row, int col, int v)
{
	int sq = squareNumber(row, col); 
	
	if (conflictRow[row - 1][v - 1] == false && conflictCol[col - 1][v - 1] == false && conflictSq[sq - 1][v - 1] == false)
	{
		//Set cell value
		value[row][col] = v;

		//Update conflict info
		conflictRow[row - 1][v - 1] = true;
		conflictCol[col - 1][v - 1] = true;
		conflictSq[sq - 1][v - 1] = true;
	}
}

void board::initialize(ifstream &fin)
// Read a Sudoku board from the input file.
{
	char ch;

	clear();

	for (int i = 1; i <= BoardSize; i++)
		for (int j = 1; j <= BoardSize; j++)
		{
			fin >> ch;

			// If the read char is not Blank
			if (ch != '.')
			{
				setCell(i, j, ch - '0');   // Convert char to int
			}
		}
}

ostream &operator<<(ostream &ostr, vector<int> &v)
// Overloaded output operator for vector class.
{
	for (int i = 0; i < v.size(); i++)
		ostr << v[i] << " ";
	ostr << endl;
	return ostr;
}

ValueType board::getCell(int i, int j)
// Returns the value stored in a cell.  Throws an exception
// if bad values are passed.
{
	if (i >= 1 && i <= BoardSize && j >= 1 && j <= BoardSize)
		return value[i][j];
	else
		throw rangeError("bad value in getCell");
}

bool board::isBlank(int i, int j)
// Returns true if cell i,j is blank, and false otherwise.
{
	if (i < 1 || i > BoardSize || j < 1 || j > BoardSize)
		throw rangeError("bad value in setCell");
}

void board::print()
// Prints the current board.
{
	for (int i = 1; i <= BoardSize; i++)
	{
		if ((i - 1) % SquareSize == 0)
		{
			cout << " -";
			for (int j = 1; j <= BoardSize; j++)
				cout << "---";
			cout << "-";
			cout << endl;
		}
		for (int j = 1; j <= BoardSize; j++)
		{
			if ((j - 1) % SquareSize == 0)
				cout << "|";
			if (!isBlank(i, j))
				cout << " " << getCell(i, j) << " ";
			else
				cout << "   ";
		}
		cout << "|";
		cout << endl;
	}

	cout << " -";
	for (int j = 1; j <= BoardSize; j++)
		cout << "---";
	cout << "-";
	cout << endl;
}