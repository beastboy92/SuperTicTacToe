#pragma once

#include "SuperTTT.h"

class ConsoleTTTGame {
public:
	explicit ConsoleTTTGame(bool computerGoesFirst);
	void askMove(SuperTTT::Side side);

	void doComputerMove();
	void play();
private:
	void printBoard() const;
	SuperTTT t;
	char computerSymbol;
	char humanSymbol;
};

