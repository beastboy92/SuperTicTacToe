#include "SuperTTT.h"

using namespace std;

SuperTTT::SuperTTT(Side s) : prow(-1), pcolumn(-1), lastPlayer(s){
	for_each(boards.begin(), boards.end(), [](Board& board){
		fill(board.begin(), board.end(), EMPTY);
	});
}

//SuperTTT::Value SuperTTT::value(int depth, int board) const {
int SuperTTT::value(int depth) const {
	if (depth == MAX_DEPTH){
		if (isAWin(COMPUTER, 0)){
			return COMPUTER_WINS;
		}
		else if (isAWin(HUMAN, 0)){
			return HUMAN_WINS;
		}
		else{
			/*array<int, 9> boardValues;
			boardValues.fill(0);*/
			int value = 0;
			for (int b = 1; b < 10; b++){
				int row = (b - 1) / 3;
				int column = (b - 1) % 3;
				// if board is won, set board value to 7 (COMPUTER_WINS) or -7 (HUMAN_WINS) else count difference between moves
				if (boards[0](row, column) == COMPUTER){
					//boardValues[b - 1] = 7;
					value += 7;
				}
				else if (boards[0](row, column) == HUMAN){
					//boardValues[b - 1] = -7;
					value -= 7;
				}
				// if there is a draw on a board, set board value to 0
				/*else if (boards[0](row, column) == FULL){
					value += 0;
					//boardValues[b - 1] = 0;
				}*/
				else if (boards[0](row, column) == EMPTY){
					for_each(boards[b].cbegin(), boards[b].cend(), [&](Side s){
						if (s == COMPUTER){
							value++;
							//boardValues[b - 1]++;
						}
						else if (s == HUMAN){
							value--;
							//boardValues[b - 1]--;
						}
					});
				}
			}
			/*for_each(boardValues.cbegin(), boardValues.cend(), [&](int v){
				value += v;
			});*/
			return value;
		}	
	}
	else{
		return isAWin(COMPUTER, 0) ? COMPUTER_WINS : isAWin(HUMAN, 0) ? HUMAN_WINS : boardIsFull(0) ? DRAW : UNDECIDED;
	}
	
	//if (depth == MAX_DEPTH){
	//	int countComputer = 0;
	//	if (board < 0 || board >10){
	//		board = giveNextBoard();
	//	}
	//	for_each(boards[board].cbegin(), boards[board].cend(), [&](Side s){
	//		if (s == COMPUTER){
	//			countComputer++;
	//		}
	//	});
	//	return isAWin(COMPUTER, board) ? COMPUTER_WINS : isAWin(HUMAN, board) ? HUMAN_WINS : boardIsFull() ? DRAW : countComputer;
	//}
	//else if (depth == MAX_DEPTH + 1){
	//	return isAWin(COMPUTER, board) ? COMPUTER_WINS : isAWin(HUMAN, board) ? HUMAN_WINS : boardIsFull() ? DRAW : UNDECIDED;
	//}
	//else{
	//	return UNDECIDED;
	//}
	//return isAWin(COMPUTER, 0) ? COMPUTER_WINS : isAWin(HUMAN, 0) ? HUMAN_WINS : boardIsFull() ? DRAW : UNDECIDED;
}


//SuperTTT::Value SuperTTT::chooseComputerMove(int& bestRow, int& bestColumn, int& bestBoard, Value alpha, Value beta, int depth) {
int SuperTTT::chooseComputerMove(int& bestRow, int& bestColumn, int& bestBoard, int alpha, int beta, int depth) {
	//Value bestValue = value(depth, bestBoard);
	int bestValue = value(depth);
	//int bestValue = value(depth, giveNextBoard());
	//int bestValue = value(depth);
	Board pMainboard = boards[0]; // preserve state of big board before function does a move
	int tmpprow = prow;		 // preserve prow before function does a move
	int tmppcolumn = pcolumn; // preservepcolumn before function does a move
	if (depth < MAX_DEPTH){
		++movesConsidered;
		if (bestValue == UNDECIDED) {
			//int nextBoard = giveNextBoard();
			//if (boards[0]((nextBoard - 1) / 3, (nextBoard - 1) % 3) != EMPTY) // somebody has won on next board
			//{
			//	nextBoard = 1;
			//}
			for (int board = 1; board < 10; ++board){
				//if (!checkFalseBoardMove(board) && !isAWin(HUMAN, board) && !isAWin(COMPUTER, board)){
				if (!checkFalseBoardMove(board) && boards[0]((board - 1) / 3, (board - 1) % 3) == EMPTY){
					for (int row = 0; alpha < beta && row < 3; ++row) {
						for (int column = 0; alpha < beta && column < 3; ++column) {
							if (boards[board](row, column) == EMPTY) {
								boards[board](row, column) = COMPUTER;
								checkWins(COMPUTER);
								prow = row;
								pcolumn = column;
								int dummyRow, dummyColumn, dummyBoard;
								//Value value = chooseHumanMove(dummyRow, dummyColumn, dummyBoard, alpha, beta, depth + 1);
								int value = chooseHumanMove(dummyRow, dummyColumn, dummyBoard, alpha, beta, depth + 1);
								boards[board](row, column) = EMPTY;
								prow = tmpprow;
								pcolumn = tmppcolumn;
								boards[0] = pMainboard; // return big board to state before the move was done
								if (value > alpha) {
									alpha = value;
									bestRow = row;
									bestColumn = column;
									bestBoard = board;
								}
							}
						}
					}
				}
			}
			bestValue = alpha;
		}
	}
	return bestValue;
}

//SuperTTT::Value SuperTTT::chooseHumanMove(int& bestRow, int& bestColumn, int& bestBoard, Value alpha, Value beta, int depth) {
int SuperTTT::chooseHumanMove(int& bestRow, int& bestColumn, int& bestBoard, int alpha, int beta, int depth) {
	//Value bestValue = value();
	int bestValue = value(depth);
	//int bestValue = value(depth, giveNextBoard());
	//int bestValue = value(depth);
	Board pMainboard = boards[0]; // preserve state of big board before function does a move
	int tmpprow = prow;		 // preserve prow before function does a move
	int tmppcolumn = pcolumn; // preservepcolumn before function does a move
	if (depth < MAX_DEPTH){
		++movesConsidered;
		if (bestValue == UNDECIDED) {
			//int nextBoard = giveNextBoard();
			//if (boards[0]((nextBoard - 1) / 3, (nextBoard - 1) % 3) != EMPTY) // somebody has won on next board
			//{
			//	nextBoard = 1;
			//}
			for (int board = 1; board < 10; ++board){
				//if (!checkFalseBoardMove(board) && !isAWin(HUMAN, board) && !isAWin(COMPUTER, board)){
				if (!checkFalseBoardMove(board) && boards[0]((board - 1) / 3, (board - 1) % 3) == EMPTY){
					for (int row = 0; beta > alpha && row < 3; ++row) {
						for (int column = 0; beta > alpha && column < 3; ++column) {
							if (boards[board](row, column) == EMPTY) {
								boards[board](row, column) = HUMAN;
								checkWins(HUMAN);
								prow = row;
								pcolumn = column;
								int dummyRow, dummyColumn, dummyBoard;
								//Value value = chooseComputerMove(dummyRow, dummyColumn, dummyBoard, alpha, beta, depth + 1);
								int value = chooseComputerMove(dummyRow, dummyColumn, dummyBoard, alpha, beta, depth + 1);
								boards[board](row, column) = EMPTY;
								prow = tmpprow;
								pcolumn = tmppcolumn;
								boards[0] = pMainboard; // return big board to state before the move was done
								if (value < beta) {
									beta = value;
									bestRow = row;
									bestColumn = column;
									bestBoard = board;
								}
							}
						}
					}
				}
			}
			bestValue = beta;
		}
		//cout << movesConsidered << endl;
	}
	return bestValue;
}

void SuperTTT::findFirstValidMove(int& validRow, int& validColumn, int& validBoard){
	for (int board = 1; board < 10; ++board){
		if (!checkFalseBoardMove(board) && boards[0]((board - 1) / 3, (board - 1) % 3) == EMPTY){
			for (int row = 0; row < 3; ++row) {
				for (int column = 0; column < 3; ++column) {
					if (boards[board](row, column) == EMPTY) {
						validRow = row;
						validColumn = column;
						validBoard = board;
						return;
					}
				}
			}
		}
	}
}

SuperTTT::Side SuperTTT::side(int row, int column, int board) const {
	return boards[board](row, column);
}

bool SuperTTT::isUndecided() const {
	return value() == UNDECIDED;
	//return value() == UNDECIDED;
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

// old function to check for draws
/*bool SuperTTT::checkDraw() const {
	int boardsLeft = 9;
	for (int b = 1; b < 10; b++){
		if (boards[0]((b-1)/3,(b-1)%3) != EMPTY){
			boardsLeft--;
		}
		else if (boardIsFull(b)){
			boardsLeft--;
		}
	}
	return (boardsLeft == 0);
}*/

bool SuperTTT::boardIsFull(int b) const {
	return none_of(boards[b].cbegin(), boards[b].cend(), [](Side s) {
		return s == EMPTY;
	});
}

bool SuperTTT::checkFalseBoardMove(int board){
	int nextBoard = (pcolumn + 1) + (prow * 3);
	if (prow == -1 && pcolumn == -1){
		return false;
	}
	//else if (isAWin(HUMAN, nextBoard) || isAWin(COMPUTER, nextBoard)){
	else if ((boards[0](prow, pcolumn) != EMPTY)){ // check if somebody has won on next board or if its a draw
		return false;
	}
	return (board != nextBoard);
}

int SuperTTT::giveNextBoard() const{
	if (prow == -1)
	{
		return 1;
	}
	else{
		return (pcolumn + 1) + (prow * 3);
	}	
}

 //old unused functions
//void SuperTTT::giveRandomBoardWhenWon(int &b){
//	if (isAWin(HUMAN, b) || isAWin(COMPUTER, b))
//	{
//		do{
//			b = (rand() % 9) + 1;
//		} while (isAWin(HUMAN, b) || isAWin(COMPUTER, b));
//	}
//}
//
//void SuperTTT::giveBestBoardWhenWon(int &board, Side s){
//	if (board < 0 || board > 9){
//		board = 0;
//	}
//	if (isAWin(HUMAN, board) || isAWin(COMPUTER, board))
//	{
//		int row, column;
//		board = 0;
//		if (s == COMPUTER)
//		{
//			chooseComputerMove(row, column, board);
//		}
//		else
//		{
//			chooseHumanMove(row, column, board);
//		}
//		if (row < 0 || row >= 3 || column < 0 || column >= 3){
//			cout << "error" << endl;
//		}
//		board = (column + 1) + (row * 3);
//	}
//	//return (board);
//}

void SuperTTT::checkWins(Side s){
	for (int i = 1; i <= 9; i++){
		if (boards[0]((i - 1) / 3, (i - 1) % 3) == EMPTY){
			if (isAWin(s, i)){
				boards[0]((i - 1) / 3, (i - 1) % 3) = s;
				//cout << "player " << s << " board " << i << endl;
			}
			else if(boardIsFull(i)){
				boards[0]((i - 1) / 3, (i - 1) % 3) = FULL;
			}
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