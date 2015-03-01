#include "Board.h"

board::board(int squareSize): value(BoardSize + 1, BoardSize + 1)	
// Board constructor
{

}

int board::squareNumber(int i, int j)
// Return the square number of cell i,j (counting from left to right,
// top to bottom.  Note that i and j each go from 1 to BoardSize
{
	// Note that (int) i/SquareSize and (int) j/SquareSize are the x-y
	// coordinates of the square that i,j is in.  

	return SquareSize * ((i - 1) / SquareSize) + (j - 1) / SquareSize + 1;
}

void board::clear(int row, int col)
// Mark all possible values as legal for each board entry
{

}

// SetCell function to define a value to a cell as well as update the
// conflict vectors accordingly
void board::setCell(int row, int col, int v)
{
	// Set cell value
	value[row][col] = v;
}

void board::initialize(ifstream &fin)
// Read a Sudoku board from the input file.
{
	char ch;
	/*int i = 1, j = 1;
	clear(i, j);*/

	for (int i = 1; i <= BoardSize; i++)
	{
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
}

ostream &operator<<(ostream &ostr, vector<int> &v)
// Overloaded output operator for vector class.
{
	for (int i = 0; i <= v.size(); i++)
		ostr << v[i] << " ";
	cout << endl;
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

	return (getCell(i, j) == Blank);
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