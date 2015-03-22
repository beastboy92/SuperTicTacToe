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
	matrix<BasicDrawPanel*, 3, 3> drawPanel;
	SuperTTT t;

	wxMenuBar *menubar;
	wxMenu *file;
	

	//void OnTextEnter(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
};