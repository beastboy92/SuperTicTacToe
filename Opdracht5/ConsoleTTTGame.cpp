#include "ConsoleTTTGame.h"

using namespace std;

ConsoleTTTGame::ConsoleTTTGame(bool computerGoesFirst) :
	computerSymbol(computerGoesFirst ? 'x' : 'o'), humanSymbol(computerGoesFirst ? 'o' : 'x') {
		if (computerGoesFirst) {
			askMove(SuperTTT::COMPUTER);
			cout << endl;
		}
}

void ConsoleTTTGame::askMove(SuperTTT::Side side){
	int board, row, column;
	do {
		printBoard();
		cout << endl << "Enter board, column and row (starts at 0): ";
		cin >> board >> column >> row;
	} while (!t.playMove(side, board, row, column));
	cout << endl;
}

void ConsoleTTTGame::play() {
	do {
		askMove(SuperTTT::HUMAN);
		if (t.isUndecided()) {
			askMove(SuperTTT::COMPUTER);
		}
	} while (t.isUndecided());
	printBoard();
	if (t.isAWin(SuperTTT::COMPUTER)) {
		cout << "Computer wins!!" << endl;
	}
	else if (t.isAWin(SuperTTT::HUMAN)) {
		cout << "Human wins!!" << endl;
	}
	else {
		cout << "Draw!!" << endl;
	}
}

void ConsoleTTTGame::printBoard() const {
	string streep("---+---+---");

	for (int row = 0; row < 9; row++){
		if (row % 3 == 0 && row != 0) {
			cout << streep << endl;
		}

		if (row < 3){
			for (int board = 1; board <= 3; board++){
				for (int column = 0; column < 3; column++){
					if (t.side(row, column, board) == SuperTTT::COMPUTER)
						cout << computerSymbol;
					else if (t.side(row, column, board) == SuperTTT::HUMAN)
						cout << humanSymbol;
					else
						cout << ' ';
				}
				if (board != 3)
					cout << "|";
			}
			cout << endl;
		}
		else if (row < 6){
			for (int board = 4; board <= 6; board++){
				for (int column = 0; column < 3; column++){
					if (t.side(row-3, column, board) == SuperTTT::COMPUTER)
						cout << computerSymbol;
					else if (t.side(row-3, column, board) == SuperTTT::HUMAN)
						cout << humanSymbol;
					else
						cout << ' ';
				}
				if (board != 6)
					cout << "|";
			}
			cout << endl;
		}
		else {
			for (int board = 7; board <= 9; board++){
				for (int column = 0; column < 3; column++){
					if (t.side(row-6, column, board) == SuperTTT::COMPUTER)
						cout << computerSymbol;
					else if (t.side(row-6, column, board) == SuperTTT::HUMAN)
						cout << humanSymbol;
					else
						cout << ' ';
				}
				if (board != 9)
					cout << "|";
			}
			cout << endl;
		}
	}
}