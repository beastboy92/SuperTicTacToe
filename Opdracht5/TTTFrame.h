#pragma once

#include <wx/wx.h>
#include "Matrix.h"
#include "BasicDrawPanel.h"
#include "SuperTTT.h"

class TTTFrame : public wxFrame
{
public:
	TTTFrame(const wxString& title);

	wxStaticText *topBar;

	//wxMenu *edit;
	//wxMenu *help;
	//wxTextCtrl *Input;
	//wxStaticText *BottomBar;
private:
	void OnExit(wxCommandEvent& event);
	void OnReset(wxCommandEvent& event);
	void mouseReleased(wxMouseEvent& event);
	matrix<BasicDrawPanel*, 3, 3> drawPanel;
	SuperTTT t;

	wxPanel *panel;
	wxMenuBar *menubar;
	wxMenu *file;
	
	static const int ID_RESET = 1;

	//void OnTextEnter(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
};