#pragma once
#ifndef GAMEBOARD_H 
#define GAMEBOARD_H

#define BOARDSIZE 10

#include <algorithm>
#include <iostream>

using namespace std;

class GameBoard
{
public:
	GameBoard();
	~GameBoard();

	void initBoard(); // Fill the board with the default character
	void displayBoard(); // Print out the board to the screen
	void updateBoard(pair <int,int>, char boardSymbol);

private:
	static char board[BOARDSIZE][BOARDSIZE]; // Declare a static array of type char the size of the BOARDSIZE definition 
};

#endif