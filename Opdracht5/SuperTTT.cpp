#include "SuperTTT.h"

using namespace std;

SuperTTT::SuperTTT() : prow(-1), pcolumn(-1), lastPlayer(SuperTTT::COMPUTER){
	for_each(boards.begin(), boards.end(), [](Board& board){
		fill(board.begin(), board.end(), EMPTY);
	});
}

SuperTTT::Value SuperTTT::value() const {
	return isAWin(COMPUTER, 0) ? COMPUTER_WINS : isAWin(HUMAN, 0) ? HUMAN_WINS : boardIsFull() ? DRAW : UNDECIDED;
}

SuperTTT::Side SuperTTT::side(int row, int column, int board) const {
	return boards[board](row, column);
}


bool SuperTTT::isUndecided() const {
	return value() == UNDECIDED;
}

bool SuperTTT::playMove(Side s, int board, int row, int column) {
	if (row < 0 || row >= 3 || column < 0 || column >= 3 || board < 1 || board > 9 || boards[board](row, column) != EMPTY || isAWin(HUMAN, board) || isAWin(COMPUTER, board) || checkFalseBoardMove(board))
		return false;
	boards[board](row, column) = s;
	prow = row;
	pcolumn = column;
	//cout << "Next board: " << (column + 1) + (row * 3) << endl;
	return true;
}

bool SuperTTT::boardIsFull() const {
	return none_of(boards[0].cbegin(), boards[0].cend(), [](Side s) {
		return s == EMPTY;
	});
}

bool SuperTTT::checkFalseBoardMove(int b){
	int nextBoard = (pcolumn + 1) + (prow * 3);
	if (prow == -1 && pcolumn == -1){
		return false;
	}
	else if (isAWin(HUMAN, nextBoard) || isAWin(COMPUTER, nextBoard)){
		return false;
	}
	return (b != nextBoard);
}

void SuperTTT::checkWins(Side s){
	for (int i = 1; i <= 9; i++){
		if (isAWin(s, i)){
			boards[0]((i - 1) / 3, (i - 1) % 3) = s;
			//cout << "player " << s << " board " << i << endl;
		}
	}
}

bool SuperTTT::isAWin(Side s, int b) const {
	for (int i = 0; i < 3; ++i) {
		if ((boards[b](i, 0) == s && boards[b](i, 1) == s && boards[b](i, 2) == s) ||
			(boards[b](0, i) == s && boards[b](1, i) == s && boards[b](2, i) == s)) {
			return true;
		}
	}
	return (boards[b](0, 0) == s && boards[b](1, 1) == s && boards[b](2, 2) == s) ||
		(boards[b](0, 2) == s && boards[b](1, 1) == s && boards[b](2, 0) == s);
}

SuperTTT::Side SuperTTT::giveLastPlayer() const{
	return lastPlayer;
}

void SuperTTT::setLastPlayer(SuperTTT::Side s){
	lastPlayer = s;
}