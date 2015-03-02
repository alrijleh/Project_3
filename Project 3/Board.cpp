#include "Board.h"

// Overloaded output operator for vector class.
template<typename T>
ostream &operator<<(ostream &ostr, vector<T> &v)
{
	for (int i = 0; i < v.size(); i++)
		ostr << v[i] << " ";
	ostr << endl;
	return ostr;
}

board::board()
{
	horzConflicts.resize(MaxValue);
	vertConflicts.resize(MaxValue);
	squareConflicts.resize(MaxValue);
}

board::~board()
{

}

// Board constructor
board::board(int squareSize): value(BoardSize + 1, BoardSize + 1)	
{
	horzConflicts.resize(MaxValue);
	vertConflicts.resize(MaxValue);
	squareConflicts.resize(MaxValue);
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
	int prevValue = value[row][col];
	value[row][col] = 0;
													//NEEDS TO REDUCE CONFLICT / COUNT VECTORS
}

// SetCell function to define a value to a cell as well as update the
// conflict vectors accordingly
void board::setCell(int row, int col, int v)
{
	// Set cell value
	if ((v >= MinValue && v <= MaxValue) || v == Blank) value[row][col] = v;
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
				ch = ch - '0'; // Convert char to int
				//if ( !checkConflicts(i, j, ch) ) //if there are no conflicts
				//{
					setCell(i, j, ch);
				//}
				//else
				//{
					//throw rangeError("invalid input board");
				//}
			}
			else
			{
				setCell(i, j, Blank);
			}
		}
	}
}

//prints the conflicts
void board::printConflicts()
{
	cout << "vertical conflicts: " << vertConflicts << endl;
	cout << "horizantal conflicts: " << horzConflicts << endl;
	cout << "square conflicts: " << squareConflicts << endl;
}

//returns true if a conflict is found
//returns false if the move is legal
bool board::checkConflicts(int i, int j, int v)
{
	if (checkHorzConflict(i, j, v)
		|| checkVertConflict(i, j, v)
		|| checkSquareConflict(i, j, v))
	{
		return true;
	}
	else return false;
}

bool board::checkVertConflict(int i, int j, int v)
{
	bool conflict = false;
	for (int index = 0; index < MaxValue; index++)
	{
		if (value[i][index] == v)
		{
			vertConflicts[j]++;
			conflict = true;
		}
	}
	return conflict;
}

bool board::checkHorzConflict(int i, int j, int v)
{
	bool conflict = false;
	for (int index = 0; index < MaxValue; index++)
	{
		if (value[index][j] == v)
		{
			horzConflicts[i]++;
			conflict = true;
		}
	}
	return conflict;
}

bool board::checkSquareConflict(int i, int j, int v)
{
	int squareNum = squareNumber(i, j);
	int squareWidth = sqrt(MaxValue);

	int baseI = ((squareNum - 1) % squareWidth) * squareWidth;
	int baseJ = ((squareNum - 1) / squareWidth) * squareWidth;
	int maxI = baseI + squareWidth;
	int maxJ = baseJ + squareWidth;

	bool conflict = false;

	for (int x = baseI; x < maxI; x++)
	{
		for (int y = baseJ; y < maxJ; y++)
		{
			if (value[x][y] == v)
			{
				squareConflicts[squareNum]++;
				conflict = true;
			}
		}
	}
	return conflict;
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
			if (b.getCell(i, j) == Blank)
			{
				cout << "Board is not solved." << endl;
				return false;
			}
		}
	}

	cout << "Board solved." << endl;
	return true;
}
