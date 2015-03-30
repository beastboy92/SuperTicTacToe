#pragma once

#include <iostream>
#include <algorithm>
#include <map>
#include <string>
#include <array>
#include "Matrix.h"

const int MAX_DEPTH = 4;

class SuperTTT{
public:
	enum Side { EMPTY, HUMAN, COMPUTER };
	enum Value { HUMAN_WINS = -1, DRAW, COMPUTER_WINS, UNDECIDED };

	SuperTTT(Side s = SuperTTT::COMPUTER);

	Value chooseComputerMove(int& bestRow, int& bestColumn, int& bestBoard, Value alpha = HUMAN_WINS, Value beta = COMPUTER_WINS, int depth = 1);
	Value chooseHumanMove(int& bestRow, int& bestColumn, int& bestBoard, Value alpha = HUMAN_WINS, Value beta = COMPUTER_WINS, int depth = 1);

	Side side(int row, int column, int board) const;
	bool isUndecided() const;
	bool playMove(Side s, int board, int row, int column);
	bool boardIsFull() const;
	bool checkFalseBoardMove(int b);
	void checkWins(Side s);
	bool isAWin(Side s, int b) const;
	Side giveLastPlayer() const;
	void setLastPlayer(Side s);
private:
	int movesConsidered = 0;
	int prow, pcolumn;
	typedef matrix<Side, 3, 3> Board;
	Board board;
	std::array<Board, 10> boards;
	Value value() const;
	Side lastPlayer;
};