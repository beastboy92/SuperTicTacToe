#pragma once

#include <wx/wx.h>

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
	//void OnTextEnter(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
};

class BasicDrawPane : public wxPanel
{

public:
	BasicDrawPane(wxFrame* parent);

	void paintEvent(wxPaintEvent & evt);
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

	DECLARE_EVENT_TABLE()
};