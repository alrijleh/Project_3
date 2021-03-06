/*
Board.cpp
Contains funcitonality for the board class

Fouad Al-Rijleh, Rachel Rudolph
*/
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
	int counter = 0;
	inRow.resize(exclusiveMax, exclusiveMax);
	inCol.resize(exclusiveMax, exclusiveMax);
	inSquare.resize(exclusiveMax, exclusiveMax);
}

board::~board()
{

}

// Board constructor
board::board(int squareSize) : value(BoardSize + 1, BoardSize + 1)
{
	int exclusiveMax = MaxValue + 1;
	int counter = 0;
	inRow.resize(exclusiveMax, exclusiveMax);
	inCol.resize(exclusiveMax, exclusiveMax);
	inSquare.resize(exclusiveMax, exclusiveMax);
}

// Return the square number of cell i,j (counting from left to right,
// top to bottom.  Note that i and j each go from 1 to BoardSize
int board::squareNumber(int i, int j)
{
	// Note that (int) i/SquareSize and (int) j/SquareSize are the x-y
	// coordinates of the square that i,j is in.  
	return (SquareSize * ((i - 1) / SquareSize) + (j - 1) / SquareSize + 1);
}

void board::clearBoard()
{
	//There should be a better way to do this
	int exclusiveMax = MaxValue + 1;
	for (int index = 0; index <= MaxValue; index++)
	{
		inRow[index].clear();
		inCol[index].clear();
		inSquare[index].clear();
		value[index].clear();

		inRow[index].resize(exclusiveMax);
		inCol[index].resize(exclusiveMax);
		inSquare[index].resize(exclusiveMax);
		value[index].resize(exclusiveMax);

		counter = 0;
	}
}

// Mark all possible values as legal for each board entry
void board::clearCell(int i, int j)
{
	int prevValue = value[i][j];
	//if (prevValue == Blank) throw rangeError("Cannot clear empty cell");
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

//Get counter of iterations
int board::getCounter()
{
	return counter;
}

// Read a Sudoku board from the input file.
void board::initialize(ifstream &fin)
{
	clearBoard();
	char ch;

	for (int i = 1; i <= BoardSize; i++)
	{
		for (int j = 1; j <= BoardSize; j++)
		{
			fin >> ch;

			// If the read char is not Blank
			if (ch != '.')
			{
				int v = int(ch - '0'); // Convert char to int
				if (!checkConflicts(i, j, v))
				{
					setCell(i, j, v);
					updateVectors(i, j, v);
				}
				else
				{
					int squareNum = squareNumber(i, j);
					if (inRow[j][v]) cout << "row " << j;
					if (inCol[i][v]) cout << "column " << i;
					if (inSquare[squareNum][v]) cout << "square " << squareNum;
					throw rangeError("Invalid input board");
				}
			}
			else
			{
				setCell(i, j, Blank);
			}
		}
	}
}

//Update bool vectors
void board::updateVectors(int i, int j, int v)
{
	int squareNum = squareNumber(i, j);

	inRow[j][v] = true;
	inCol[i][v] = true;
	inSquare[squareNum][v] = true;
}

//Check for conflicts within row, col, sq
bool board::checkConflicts(int i, int j, int v)
{
	int squareNum = squareNumber(i, j);
	return (inRow[j][v] || inCol[i][v] || inSquare[squareNum][v]);
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

//Solve sudoku board
void board::solve()
{
	//Counts number of times solve() is called
	counter++;

	//Check if board is already solved
	if (checkSolved())
	{
		print();
		cout << "Solved." << endl;
		cout << "Number of iterations: " << counter << endl;
		return;
	}
	else
	{
		vector<int> location(2, -1);
		location = findBestBlank();
		int i = location[0];
		int j = location[1];

		for (int v = 1; v <= MaxValue; v++)
		{
			if (!checkConflicts(i, j, v))
			{
				setCell(i, j, v);
				updateVectors(i, j, v);
				solve();
				clearCell(i, j);
			}
		}
		clearCell(i, j);
	}


}

//Count possible values for each cell in board
int board::countPossibleValues(int i, int j)
{
	int possibilities = 0;
	for (int v = 1; v <= MaxValue; v++)
	{
		if (!checkConflicts(i, j, v))
		{
			possibilities++;
		}
	}
	return possibilities;
}

//Find blank cell with least amount of possibilities
vector<int> board::findBestBlank()
{
	int possibilities;
	vector<int> location(2, -1);
	vector<Cell> possibleValueList;
	Cell cell;
	for (int i = 1; i <= BoardSize; i++)
	{
		for (int j = 1; j <= BoardSize; j++)
		{
			if (getCell(i, j) == Blank)
			{
				possibilities = countPossibleValues(i, j);
				if (possibilities == 1)
				{
					location = { i, j };
					return location;
				}
				else
				{
					cell.setLocation(i, j);
					cell.setValue(possibilities);
					possibleValueList.push_back(cell);
				}
			}
		}
	}
	location = findMinimumLocation(possibleValueList);
	return location;
}

//Find location of cell with fewest possibilites
vector<int> board::findMinimumLocation(vector<Cell> cellVector)
{
	int minimum = 9;
	vector<int> minimumLocation;
	for (int index = 0; index < cellVector.size(); index++)
	{
		if (cellVector[index].getValue() < minimum)
		{
			minimum = cellVector[index].getValue();
			minimumLocation = cellVector[index].getLocation();
		}
	}

	return minimumLocation;
}

//Find next blank cell in board
vector<int> board::findNextBlank()
{
	vector<int> location(2, -1);
	for (int i = 1; i <= BoardSize; i++)
	{
		for (int j = 1; j <= BoardSize; j++)
		{
			if (getCell(i, j) == Blank)
			{
				location = { i, j };
				return location;
			}
		}
	}
	return location;
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

//Print conflicts in board
void board::printConflicts() {
	cout << "Conflicts for Rows " << endl;
	for (int i = 0; i < BoardSize; i++)
	{
		for (int j = 0; j < BoardSize; j++)
		{
			cout << inRow[i][j] << " ";
		}
		cout << endl;
	}

	cout << "Conflicts for Columns " << endl;
	for (int i = 0; i < BoardSize; i++)
	{
		for (int j = 0; j < BoardSize; j++)
		{
			cout << inCol[i][j] << " ";
		}
		cout << endl;
	}

	cout << "Conflicts for Squares " << endl;
	for (int i = 0; i < BoardSize; i++)
	{
		for (int j = 0; j < BoardSize; j++)
		{
			cout << inSquare[i][j] << " ";
		}
		cout << endl;
	}
}

//Check to see if board is solved
bool board::checkSolved()
{
	for (int i = 1; i <= BoardSize; i++)
	{
		for (int j = 1; j <= BoardSize; j++)
		{
			//If any cells are blank, board is not solved.
			if (value[i][j] == Blank)
			{
				return false;
			}
		}
	}
	return true;
}
