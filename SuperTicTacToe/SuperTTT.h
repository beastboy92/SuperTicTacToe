#pragma once

#include <iostream>
#include <algorithm>
#include <map>
#include <string>
#include <array>
#include "Matrix.h"
/* Depth index
	9 = fast and hard to win
	10 = fast and undefeatable?
	12 = slower (+/- 1 second)
*/


class SuperTTT{
public:
	enum Side { EMPTY, HUMAN, COMPUTER, FULL};
	enum Value { HUMAN_WINS = -52, DRAW = 0, COMPUTER_WINS = 52, UNDECIDED = 53};

	SuperTTT(Side s = SuperTTT::COMPUTER, const int DEPTH = 9);

	int chooseComputerMove(int& bestRow, int& bestColumn, int& bestBoard, int alpha = HUMAN_WINS, int beta = COMPUTER_WINS, int depth = 1);
	int chooseHumanMove(int& bestRow, int& bestColumn, int& bestBoard, int alpha = HUMAN_WINS, int = COMPUTER_WINS, int depth = 1);

	void findFirstValidMove(int& validRow, int& validColumn, int& validBoard);

	Side side(int row, int column, int board) const;
	bool isUndecided() const;
	bool playMove(Side s, int board, int row, int column);
	bool boardIsFull(int b) const;
	bool checkFalseBoardMove(int board);
	int giveNextBoard() const;
	void checkWins(Side s);
	bool isAWin(Side s, int b) const;
	Side giveLastPlayer() const;
	void setLastPlayer(Side s);
private:
	int movesConsidered = 0;
	int prow, pcolumn;
	const int MAX_DEPTH;
	typedef matrix<Side, 3, 3> Board;
	//Board board;
	std::array<Board, 10> boards;
	int value(int depth = 0) const;
	Side lastPlayer;
};
