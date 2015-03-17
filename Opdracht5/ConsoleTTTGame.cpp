#include "ConsoleTTTGame.h"

using namespace std;

ConsoleTTTGame::ConsoleTTTGame(bool computerGoesFirst) :
	computerSymbol(computerGoesFirst ? 'x' : 'o'), humanSymbol(computerGoesFirst ? 'o' : 'x') {
		if (computerGoesFirst) {
			askMove(SuperTTT::COMPUTER);
			cout << endl;
		}
	//printBoard();
}

void ConsoleTTTGame::askMove(SuperTTT::Side side){
	int row, column;
	do {
		printBoard();
		cout << endl << "Enter column and row (starts at 0): ";
		cin >> column >> row;
	} while (!t.playMove(side, row, column));
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
	string streep(3, '-');
	cout << streep << endl;
	for (int row = 0; row < 3; ++row) {
		for (int column = 0; column < 3; ++column)
		{
			if (t.side(row, column) == SuperTTT::COMPUTER)
				cout << computerSymbol;
			else if (t.side(row, column) == SuperTTT::HUMAN)
				cout << humanSymbol;
			else
				cout << ' ';
		}
		cout << endl;
	}
	/*for (int row = 0; row < 9; row++){
		if (row < 3){
			for (int board = 1; board <= 3; board++){
				for (int column = 0; column < 3; column++){
					if (t.side(row, column, board) == SuperTTT::COMPUTER)
						cout << computerSymbol;
					else if (t.side(row, column, board) == SuperTTT::HUMAN)
						cout << humanSymbol;
					else
						cout << 'G';
				}
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
						cout << 'H';
				}
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
						cout << 'I';
				}
			}
			cout << endl;
		}
	}*/
	cout << streep << endl;
}