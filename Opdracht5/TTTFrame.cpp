#include "TTTFrame.h"
#include <algorithm>

wxBEGIN_EVENT_TABLE(TTTFrame, wxFrame)
EVT_MENU(wxID_EXIT, TTTFrame::OnExit)
EVT_MENU(TTTFrame::ID_RESET, TTTFrame::OnReset)
wxEND_EVENT_TABLE()

TTTFrame::TTTFrame(const wxString& title)
: wxFrame(NULL, -1, title, wxDefaultPosition, wxGetDisplaySize())//wxSize(900,925))
{
	panel = new wxPanel(this, -1);
	wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
	//wxGridSizer *gridBox = new wxGridSizer(3, 3, 2, 2);

	topBar = new wxStaticText(panel, -1, wxT("Welcome to Tic Tac Toe"));

	/*BasicDrawPanel *drawPanel1 = new BasicDrawPanel(panel, true);
	BasicDrawPanel *drawPanel2 = new BasicDrawPanel(panel, false);
	BasicDrawPanel *drawPanel3 = new BasicDrawPanel(panel, true);
	BasicDrawPanel *drawPanel4 = new BasicDrawPanel(panel, false);
	BasicDrawPanel *drawPanel5 = new BasicDrawPanel(panel, true);
	BasicDrawPanel *drawPanel6 = new BasicDrawPanel(panel, false);
	BasicDrawPanel *drawPanel7 = new BasicDrawPanel(panel, true);
	BasicDrawPanel *drawPanel8 = new BasicDrawPanel(panel, false);
	BasicDrawPanel *drawPanel9 = new BasicDrawPanel(panel, true);*/

	
	wxSize size = wxGetDisplaySize();
	int sizeY = size.GetY();
	size = topBar->GetSize();
	sizeY = (sizeY - 200 - 30 - 12)/9;
	
	int i = 0;
	for (int board = 0; board < 10; ++board)
	{
		for (int row = 0; row < 3; ++row) {
			for (int column = 0; column < 3; ++column)
			{
				drawPanels[board](row, column) = new BasicDrawPanel(panel, t, i++, sizeY);
			}
		}
	}

	for (auto p : drawPanels[0])
	{
		delete p;
	}

	
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

	for (i = 1; i < 10; i++)
	{
		playField[i] = new wxGridSizer(3, 3, 2, 2);
		for (int row = 0; row < 3; ++row) {
			for (int column = 0; column < 3; ++column)
			{
				playField[i]->Add(drawPanels[i](row, column));
				//gridBox->Add(drawPanel(row, column));
			}
		}
		playField[0]->Add(playField[i]);
	}

	vbox->Add(topBar, 0, wxEXPAND);
	vbox->Add(playField[0], 0, wxALIGN_CENTER);
	panel->SetSizer(vbox);
	
	menubar = new wxMenuBar;
	file = new wxMenu;

	file->Append(ID_RESET, wxT("&Reset\tAlt+R"));
	file->Append(wxID_EXIT, wxT("&Exit"));
	menubar->Append(file, wxT("&File"));

	SetMenuBar(menubar);
	size = playField[0]->GetSize();
	size.Set(size.GetWidth() + 50, size.GetHeight() + 3*topBar->GetSize().GetHeight() + 45);
	//size = panel->GetSize();
	SetInitialSize(size);
	SetMaxSize(size);
}

void TTTFrame::SetTopBar(std::string message){
	topBar->SetLabel(message);
}

void TTTFrame::OnExit(wxCommandEvent& event)
{
	Close(true);
}

void TTTFrame::OnReset(wxCommandEvent& event)
{
	t = SuperTTT();
	/*for (auto panel : drawPanels) {
		for (auto p : panel){
			p->resetClick();
			p->paintNow();
		}		
	};*/

	std::for_each(drawPanels.cbegin() + 1, drawPanels.cend(), [](DrawPanel panel){
		for (auto p : panel){
			p->resetClick();
			p->paintNow();
		}
	});

	topBar->SetLabel(wxT("New Game"));
}

