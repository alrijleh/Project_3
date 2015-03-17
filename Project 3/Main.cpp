/*
Main.cpp
Contains main function body

Fouad Al-Rijleh, Rachel Rudolph
*/
// Declarations and functions for project #4

#include "Main.h"

using namespace std;

int main()
{
	ifstream fin;

	// Read the sample grid from the file.
	string fileName = "sudoku.txt";

	fin.open(fileName.c_str());
	if (!fin)
	{
		cerr << "Cannot open " << fileName << endl;
		exit(1);
	}

	try
	{
		board b1(SquareSize);

		while (fin && fin.peek() != 'Z')
		{
			b1.initialize(fin);
			b1.print();
			b1.solve();
			//b1.printConflicts();
			//b1.checkSolved();
			cout << "Number of iterations: " << b1.getCounter() << endl;
			system("pause");
		}
		system("pause");
	}
	catch (indexRangeError &ex)
	{
		cout << ex.what() << endl;
		exit(1);
	}
}
