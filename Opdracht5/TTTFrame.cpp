#include "TTTFrame.h"
#include <algorithm>

wxBEGIN_EVENT_TABLE(TTTFrame, wxFrame)
EVT_MENU(wxID_EXIT, TTTFrame::OnExit)
EVT_MENU(TTTFrame::ID_RESET, TTTFrame::OnReset)
EVT_MENU(TTTFrame::ID_PvP, TTTFrame::OnPvP)
wxEND_EVENT_TABLE()

TTTFrame::TTTFrame(const wxString& title, bool computerFirst)
: wxFrame(NULL, -1, title, wxDefaultPosition, wxGetDisplaySize()), computerFirst(computerFirst)
{
	t = SuperTTT(computerFirst ? SuperTTT::HUMAN : SuperTTT::COMPUTER);
	panel = new wxPanel(this, -1);
	wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);

	topBar = new wxStaticText(panel, -1, wxT("Welcome to Tic Tac Toe"));
	
	wxSize size = wxGetDisplaySize();
	int sizeY = size.GetY();
	size = topBar->GetSize();
	sizeY = (sizeY - 200 - 30 - 12)/9;
	
	for (int board = 1; board < 10; ++board)
	{
		for (int row = 0; row < 3; ++row) {
			for (int column = 0; column < 3; ++column)
			{
				drawPanels[board](row, column) = new BasicDrawPanel(panel, t, board, row, column, sizeY);
			}
		}
	}

	/*for (auto p : drawPanels[0])
	{
		delete p;
	}*/

	
	/*gridBox->Add(drawPanel1, 0);
	gridBox->Add(drawPanel2, 0);
	gridBox->Add(drawPanel3, 0);
	gridBox->Add(drawPanel4, 0);
	gridBox->Add(drawPanel5, 0);
	gridBox->Add(drawPanel6, 0);
	gridBox->Add(drawPanel7, 0);
	gridBox->Add(drawPanel8, 0);
	gridBox->Add(drawPanel9, 0);*/

	playField[0] = new wxGridSizer(3, 3, 15, 15);

	for (int i = 1; i < 10; i++)
	{
		playField[i] = new wxGridSizer(3, 3, 2, 2);
		for (int row = 0; row < 3; ++row) {
			for (int column = 0; column < 3; ++column)
			{
				playField[i]->Add(drawPanels[i](row, column));
			}
		}
		playField[0]->Add(playField[i]);
	}

	vbox->Add(topBar, 0, wxEXPAND);
	vbox->Add(playField[0], 0, wxALIGN_CENTER);
	panel->SetSizer(vbox);
	
	menubar = new wxMenuBar;
	file = new wxMenu;
	settings = new wxMenu;

	file->Append(ID_RESET, wxT("&Reset\tAlt+R"));
	file->Append(wxID_EXIT, wxT("&Exit"));
	menubar->Append(file, wxT("&File"));

	settings->Append(ID_PvP, wxT("&PvP"), wxT("Player vs Player"), true);
	PvP = false;
	menubar->Append(settings, wxT("&Settings"));

	SetMenuBar(menubar);
	size = playField[0]->GetSize();
	size.Set(size.GetWidth() + 50, size.GetHeight() + 3*topBar->GetSize().GetHeight() + 45);
	SetInitialSize(size);
	SetMaxSize(size);
}

void TTTFrame::doComputerMove(){
	if (t.isUndecided()){
		int y = topBar->GetSize().GetHeight();
		int x = panel->GetSize().GetWidth() - 50;
		topBar->SetSize(x, y);
		topBar->SetLabel(wxT("Computer is deciding move"));
		int bestRow, bestColumn, bestBoard;
		//bestBoard = t.giveNextBoard();
		//t.giveRandomBoardWhenWon(bestBoard); // prevent computer to set on board that is won
		//t.giveBestBoardWhenWon(bestBoard, SuperTTT::COMPUTER); // prevent computer to set on board that is won and give best board to set next move
		t.chooseComputerMove(bestRow, bestColumn, bestBoard);

		drawPanels[bestBoard](bestRow, bestColumn)->computerMove();
	}
}

bool TTTFrame::GivePvP(){
	return PvP;
}

void TTTFrame::SetTopBar(const wxString &message){
	topBar->SetLabel(message);
}

void TTTFrame::OnExit(wxCommandEvent& event)
{
	Close(true);
}

void TTTFrame::OnReset(wxCommandEvent& event)
{
	computerFirst = !computerFirst;
	// make a new game
	t = SuperTTT(computerFirst ? SuperTTT::HUMAN : SuperTTT::COMPUTER);

	//reset all panels
	std::for_each(drawPanels.cbegin() + 1, drawPanels.cend(), [](DrawPanel panel){
		for (auto p : panel){
			p->resetClick();
			p->paintNow();
		}
	});

	topBar->SetLabel(wxT("New Game"));
	if (computerFirst && ! PvP){
		doComputerMove();
	}
}

void TTTFrame::OnPvP(wxCommandEvent& event)
{
	PvP = !PvP;
}

