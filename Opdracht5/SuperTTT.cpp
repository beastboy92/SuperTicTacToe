#include "SuperTTT.h"

using namespace std;

SuperTTT::SuperTTT() : lastPlayer(SuperTTT::COMPUTER){
	fill(board.begin(), board.end(), EMPTY);
	/*for_each(boards.begin(), boards.end(), [](Board& board){
		fill(board.begin(), board.end(), EMPTY);
	});*/
}

SuperTTT::Value SuperTTT::value() const {
	return isAWin(COMPUTER) ? COMPUTER_WINS : isAWin(HUMAN) ? HUMAN_WINS : boardIsFull() ? DRAW : UNDECIDED;
}

//SuperTTT::Side SuperTTT::side(int row, int column, int board) const {
//	return boards[board](row, column);
//}

SuperTTT::Side SuperTTT::side(int row, int column) const {
	return board(row, column);
}

bool SuperTTT::isUndecided() const {
	return value() == UNDECIDED;
}

bool SuperTTT::playMove(Side s, int row, int column) {
	if (row < 0 || row >= 3 || column < 0 || column >= 3 || board(row, column) != EMPTY)
		return false;

	board(row, column) = s;
	return true;
}

bool SuperTTT::boardIsFull() const {
	return none_of(board.cbegin(), board.cend(), [](Side s) {
		return s == EMPTY;
	});
	return true;
}

bool SuperTTT::isAWin(Side s) const {
	for (int i = 0; i < 3; ++i) {
		if ((board(i, 0) == s && board(i, 1) == s && board(i, 2) == s) ||
			(board(0, i) == s && board(1, i) == s && board(2, i) == s)) {
			return true;
		}
	}
	return (board(0, 0) == s && board(1, 1) == s && board(2, 2) == s) ||
		(board(0, 2) == s && board(1, 1) == s && board(2, 0) == s);
	return true;
}

SuperTTT::Side SuperTTT::giveLastPlayer() const{
	return lastPlayer;
}

void SuperTTT::setLastPlayer(SuperTTT::Side s){
	lastPlayer = s;
}