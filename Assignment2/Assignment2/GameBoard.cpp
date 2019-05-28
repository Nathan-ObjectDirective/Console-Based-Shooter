#include "GameBoard.h"

char GameBoard::board[BOARDSIZE][BOARDSIZE];

GameBoard::GameBoard()
{
}

GameBoard::~GameBoard()
{
}

// Refresh the board, clearing any old details.
void GameBoard::initBoard()
{
	for (int i = 0; i<BOARDSIZE; i++)
	{
		for (int j = 0; j<BOARDSIZE; j++)
		{
			board[i][j] = ' ';
		}
	}
}

/*
	As the console draws the board from top right downwards and I want the x,y to have a bottom left origin,
	I had to jump through some hoops to print this out correctly. TODO improve this function.
*/
void GameBoard::displayBoard()
{
	system("CLS");
	cout << "\n\n				    **********************" << endl;

	for (int i = BOARDSIZE-1; i >= 0; i--) // i=y
	{
		if (i < 10)
		{
			cout << "				  " << i << " |";
		}
		else
		{
			cout << "				 " << i << " |";
		}
		for (int j = 0; j < BOARDSIZE; j++) // j=x
		{
			cout << " " << board[j][i]; // j, i switch

		}
		cout << "|" << endl;
	}
	cout << "				  y **********************\n";
	cout << "		      		    x 0 1 2 3 4 5 6 7 8 9\n";
}

// Update the board with the position to update and what to put in it.
void GameBoard::updateBoard(pair<int, int> coords, char name)
{
	int x = coords.first;
	int y = coords.second;

	board[x][y] = name;
}
