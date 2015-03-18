#include "SuperTTT.h"

using namespace std;

SuperTTT::SuperTTT(){
	for_each(boards.begin(), boards.end(), [](Board& board){
		fill(board.begin(), board.end(), EMPTY);
	});
}

SuperTTT::Value SuperTTT::value() const {
	return isAWin(COMPUTER) ? COMPUTER_WINS : isAWin(HUMAN) ? HUMAN_WINS : boardIsFull() ? DRAW : UNDECIDED;
}

SuperTTT::Side SuperTTT::side(int row, int column, int board) const {
	return boards[board](row, column);
}

bool SuperTTT::isUndecided() const {
	return value() == UNDECIDED;
}

bool SuperTTT::playMove(Side s, int board, int row, int column) {
	if (row < 0 || row >= 3 || column < 0 || column >= 3 || board < 1 || board > 9 || boards[board](row, column) != EMPTY)
		return false;
	boards[board](row, column) = s;
	return true;
}

bool SuperTTT::boardIsFull() const {
	return none_of(boards[0].cbegin(), boards[0].cend(), [](Side s) {
		return s == EMPTY;
	});
}

bool SuperTTT::isAWin(Side s) const {
	for (int i = 0; i < 3; ++i) {
		if ((boards[0](i, 0) == s && boards[0](i, 1) == s && boards[0](i, 2) == s) ||
			(boards[0](0, i) == s && boards[0](1, i) == s && boards[0](2, i) == s)) {
			return true;
		}
	}
	return (boards[0](0, 0) == s && boards[0](1, 1) == s && boards[0](2, 2) == s) ||
		(boards[0](0, 2) == s && boards[0](1, 1) == s && boards[0](2, 0) == s);
}