#pragma once

#include <wx/wx.h>
#include "SuperTTT.h"

class BasicDrawPanel : public wxPanel
{

public:
	BasicDrawPanel(wxPanel* parent, SuperTTT& t, int panel, int size);

	void paintEvent(wxPaintEvent & evt);
	void mouseDown(wxMouseEvent& event);
	void mouseReleased(wxMouseEvent& event);
	void paintNow();
	void resetClick();
	void computerMove();
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
	int panel;
	SuperTTT& t;

	wxDECLARE_EVENT_TABLE();
};