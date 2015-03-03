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

	int exclusiveMax = MaxValue + 1;
	inRow.resize(exclusiveMax, exclusiveMax);
	inCol.resize(exclusiveMax, exclusiveMax);
	inSquare.resize(exclusiveMax, exclusiveMax);
}

board::~board()
{

}

// Board constructor
board::board(int squareSize): value(BoardSize + 1, BoardSize + 1)	
{
	int exclusiveMax = MaxValue + 1;
	inRow.resize(exclusiveMax, exclusiveMax);
	inCol.resize(exclusiveMax, exclusiveMax);
	inSquare.resize(exclusiveMax, exclusiveMax);
}

// Return the square number of cell i,j (counting from left to right,
// top to bottom.  Note that i and j each go from 0 to BoardSize - 1
int board::squareNumber(int i, int j)
{
	// Note that (int) i/SquareSize and (int) j/SquareSize are the x-y
	// coordinates of the square that i,j is in.  

	return (SquareSize * ((i - 1) / SquareSize) + (j - 1) / SquareSize + 1) - 1;
}

// Mark all possible values as legal for each board entry
void board::clear(int i, int j)
{
	int prevValue = value[i][j];
	int squareNum = squareNumber(i, j);
	value[i][j] = Blank;
	
	//Clears recording from vector
	inRow[j][prevValue] = false;
	inCol[i][prevValue] = false;
	inSquare[squareNum][prevValue] = false;
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
				setCell(i, j, ch);
				updateVectors(i , j , ch);
			}
			else
			{
				setCell(i, j, Blank);
			}
		}
	}
}

void board::updateVectors(int i, int j, int v)
{
	int squareNum = squareNumber(i, j);

	inRow[j][v] = true;
	inCol[i][v] = true;
	inSquare[squareNum][v] = true;
}

bool board::checkConflicts(int i, int j, int v)
{
	return (inRow[j][v] || inCol[i][v] || inSquare[i][j]);
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
