#include "TTTFrame.h"

wxBEGIN_EVENT_TABLE(TTTFrame, wxFrame)
EVT_MENU(wxID_EXIT, TTTFrame::OnExit)
wxEND_EVENT_TABLE()

TTTFrame::TTTFrame(const wxString& title)
: wxFrame(NULL, -1, title, wxDefaultPosition, wxSize(300, 325))
{
	wxPanel *panel = new wxPanel(this, -1);
	wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
	wxGridSizer *gridBox = new wxGridSizer(3, 3, 2, 2);

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

	int i = 0;
	for (int row = 0; row < 3; ++row) {
		for (int column = 0; column < 3; ++column)
		{
			drawPanel(row, column) = new BasicDrawPanel(panel, &t, i++);
		}
	}

	vbox->Add(topBar, 0, wxEXPAND);
	vbox->Add(gridBox, 0, wxALIGN_CENTER);

	/*gridBox->Add(drawPanel1, 0);
	gridBox->Add(drawPanel2, 0);
	gridBox->Add(drawPanel3, 0);
	gridBox->Add(drawPanel4, 0);
	gridBox->Add(drawPanel5, 0);
	gridBox->Add(drawPanel6, 0);
	gridBox->Add(drawPanel7, 0);
	gridBox->Add(drawPanel8, 0);
	gridBox->Add(drawPanel9, 0);*/

	for (int row = 0; row < 3; ++row) {
		for (int column = 0; column < 3; ++column)
		{
			gridBox->Add(drawPanel(row, column));
		}
	}
	panel->SetSizer(vbox);

	SetMinSize(wxSize(300, 325));
	SetMaxSize(wxSize(300, 325));

	menubar = new wxMenuBar;
	file = new wxMenu;

	file->Append(wxID_EXIT, wxT("&Exit"));
	menubar->Append(file, wxT("&File"));

	SetMenuBar(menubar);
}

void TTTFrame::OnExit(wxCommandEvent& event)
{
	Close(true);
}
