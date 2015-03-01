#include "Board.h"

// Board constructor
board::board(int squareSize): value(BoardSize + 1, BoardSize + 1)	
{

}

// Return the square number of cell i,j (counting from left to right,
// top to bottom.  Note that i and j each go from 1 to BoardSize
int board::squareNumber(int i, int j)
{
	// Note that (int) i/SquareSize and (int) j/SquareSize are the x-y
	// coordinates of the square that i,j is in.  

	return SquareSize * ((i - 1) / SquareSize) + (j - 1) / SquareSize + 1;
}

// Mark all possible values as legal for each board entry
void board::clear(int row, int col)
{

}

// SetCell function to define a value to a cell as well as update the
// conflict vectors accordingly
void board::setCell(int row, int col, int v)
{
	// Set cell value
	if (v >= MinValue && v <= MaxValue) value[row][col] = v;
	else throw rangeError("Value in grid must be between MinValue and MaxValue");
}

// Read a Sudoku board from the input file.
void board::initialize(ifstream &fin)
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

bool board::checkConflicts(int i, int j, int v)
{
	//check horizantal
	for (int index = 0; index < MaxValue; index++)
	{
		if (value[index][j] == v) return false;
	}

	//check vertical
	for (int index = 0; index < MaxValue; index++)
	{
		if (value[i][index] == v) return false;
	}

	//check square
	int squareNum = squareNumber(i, j);
	int squareWidth = sqrt(MaxValue);

	int baseI = ((squareNum - 1) % squareWidth) * squareWidth;
	int baseJ = ((squareNum - 1) / squareWidth) * squareWidth;

	for (int x = baseI; x < x + squareWidth; x++)
	{
		for (int y = baseJ; y < y + squareWidth; y++)
		{
			if (value[x][y] == v) return false;
		}
	}
	
	//no conflicts were found
	return true;
}

// Returns the value stored in a cell.  Throws an exception
// if bad values are passed.
ValueType board::getCell(int i, int j)
{
	if (i >= 1 && i <= BoardSize && j >= 1 && j <= BoardSize)
		return value[i][j];
	else
		throw rangeError("bad value in getCell");
}

// Returns true if cell i,j is blank, and false otherwise.
bool board::isBlank(int i, int j)
{
	if (i < 1 || i > BoardSize || j < 1 || j > BoardSize)
		throw rangeError("bad value in setCell");

	return (getCell(i, j) == Blank);
}

// Prints the current board.
void board::print()
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

//Check to see if board is solved
bool board::checkSolved(board b)
{
	for (int i = 1; i <= BoardSize; i++)
	{
		for (int j = 1; j <= BoardSize; j++)
		{
			//If any cells are 0, board is not solved.
			if (b.getCell(i, j) == 0)
			{
				cout << "Board is not solved." << endl;
				return false;
			}
		}
	}

	cout << "Board solved." << endl;
	return true;
}

// Overloaded output operator for vector class.
ostream &operator<<(ostream &ostr, vector<int> &v)
{
	for (int i = 0; i <= v.size(); i++)
		ostr << v[i] << " ";
	ostr << endl;
	return ostr;
}