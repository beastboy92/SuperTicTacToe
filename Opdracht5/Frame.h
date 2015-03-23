#pragma once

#include <wx/wx.h>
#include "Matrix.h"

class BasicDrawPanel : public wxPanel
{

public:
	BasicDrawPanel(wxPanel* parent, bool cross);

	void paintEvent(wxPaintEvent & evt);
	void mouseDown(wxMouseEvent& event);
	void paintNow();

	void render(wxDC& dc);

	// some useful events
	/*
	void mouseMoved(wxMouseEvent& event);
	void mouseDown(wxMouseEvent& event);
	void mouseWheelMoved(wxMouseEvent& event);
	void mouseReleased(wxMouseEvent& event);
	void rightClick(wxMouseEvent& event);
	void mouseLeftWindow(wxMouseEvent& event);
	void keyPressed(wxKeyEvent& event);
	void keyReleased(wxKeyEvent& event);
	*/

private:
	bool cross;
	bool click;

	wxDECLARE_EVENT_TABLE();
};

class TTTFrame : public wxFrame
{
public:
	TTTFrame(const wxString& title);

	wxMenuBar *menubar;
	wxMenu *file;
	//wxMenu *edit;
	//wxMenu *help;
	//wxTextCtrl *Input;
	//wxStaticText *BottomBar;
private:
	void OnExit(wxCommandEvent& event);
	matrix<BasicDrawPanel*, 3, 3> drawPanel;
	//void OnTextEnter(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
};
