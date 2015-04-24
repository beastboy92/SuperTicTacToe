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
	//void SetTopBar(std::string message);
	void SetTopBar(const wxString &message);
	void doComputerMove();
	bool GivePvP();
	SuperTTT* giveGame();

	//wxMenu *edit;
	//wxMenu *help;
	//wxTextCtrl *Input;
	//wxStaticText *BottomBar;
private:
	void OnExit(wxCommandEvent& event);
	void OnReset(wxCommandEvent& event);
	void OnPvP(wxCommandEvent& event);
	void On1(wxCommandEvent& event);
	void On5(wxCommandEvent& event);
	void On9(wxCommandEvent& event);
	void On10(wxCommandEvent& event);
	void On12(wxCommandEvent& event);
	void Reset();
	//void mouseReleased(wxMouseEvent& event);
	typedef matrix<BasicDrawPanel*, 3, 3> DrawPanel;
	//DrawPanel drawPanel;

	std::array<DrawPanel, 10> drawPanels; // [0] unused but for future use
	std::array<wxGridSizer*, 10> playField;
	SuperTTT* t;

	wxPanel *panel;
	wxMenuBar *menubar;
	wxMenu *file;
	wxMenu *settings;
	wxMenu *difficulty;
	wxStaticText *topBar;
	
	static const int ID_RESET = 1;
	static const int ID_PvP = 2;
	static const int ID_1 = 3;
	static const int ID_5 = 4;
	static const int ID_9 = 5;
	static const int ID_10 = 6;
	static const int ID_12 = 7;

	bool computerFirst;
	bool PvP;
	bool easy;
	bool medium;
	bool hard;
	bool extreme;
	bool unwinnable;

	//void OnTextEnter(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
};