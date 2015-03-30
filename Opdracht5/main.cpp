//#include "ConsoleTTTGame.h"
//
//using namespace std;
//
//int main(){
//	cout << "Welcome to TIC-TAC-TOE" << endl;
//	bool computerGoesFirst = true;
//	char again;
//	do {
//		ConsoleTTTGame game(computerGoesFirst);
//		game.play();
//		do {
//			cout << "Play again (y/n)? ";
//			cin >> again;
//		} while (again != 'y' && again != 'Y' && again != 'n' && again != 'N');
//		computerGoesFirst = !computerGoesFirst;
//		cout << endl;
//	} while (again != 'n' && again != 'N');
//	return 0;
//}
//}


#include "main.h"
#include "TTTFrame.h"

IMPLEMENT_APP(TTTApp)

bool TTTApp::OnInit()
{

	TTTFrame *tttFrame = new TTTFrame(wxT("Tic Tac Toe"), false);
	tttFrame->Show(true);

	return true;
}




