#pragma once

#include <wx/wx.h>
#include "Matrix.h"
#include "BasicDrawPanel.h"
#include "SuperTTT.h"
#include <array>
#include <string>

class TTTFrame : public wxFrame
{
public:
	TTTFrame(const wxString& title, bool computerFirst);
	void SetTopBar(std::string message);

	//wxMenu *edit;
	//wxMenu *help;
	//wxTextCtrl *Input;
	//wxStaticText *BottomBar;
private:
	void OnExit(wxCommandEvent& event);
	void OnReset(wxCommandEvent& event);
	//void mouseReleased(wxMouseEvent& event);
	typedef matrix<BasicDrawPanel*, 3, 3> DrawPanel;
	//DrawPanel drawPanel;

	std::array<DrawPanel, 10> drawPanels;
	std::array<wxGridSizer*, 10> playField;
	SuperTTT t;

	wxPanel *panel;
	wxMenuBar *menubar;
	wxMenu *file;
	wxStaticText *topBar;
	
	static const int ID_RESET = 1;

	bool computerFirst;

	//void OnTextEnter(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
};