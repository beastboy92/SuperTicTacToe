#pragma once

#include <iostream>
#include <algorithm>
#include <map>
#include <string>
#include <array>
#include "Matrix.h"

class SuperTTT{
public:
	SuperTTT();

	enum Side { EMPTY, HUMAN, COMPUTER };
	enum Value { HUMAN_WINS = -1, DRAW, COMPUTER_WINS, UNDECIDED };

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
	int prow, pcolumn;
	typedef matrix<Side, 3, 3> Board;
	Board board;
	std::array<Board, 10> boards;
	Value value() const;
	Side lastPlayer;
};