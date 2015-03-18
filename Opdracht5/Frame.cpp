#include "Frame.h"

wxBEGIN_EVENT_TABLE(TTTFrame, wxFrame)
EVT_MENU(wxID_EXIT, TTTFrame::OnExit)
wxEND_EVENT_TABLE()

TTTFrame::TTTFrame(const wxString& title)
: wxFrame(NULL, -1, title, wxDefaultPosition, wxSize(800, 600))
{
	wxPanel *panel = new wxPanel(this, -1);
	wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);

	BasicDrawPane *drawPanel1 = new BasicDrawPane((wxFrame*)panel);
	BasicDrawPane *drawPanel2 = new BasicDrawPane((wxFrame*)panel);
	
	vbox->Add(drawPanel1, 1, wxEXPAND);
	vbox->Add(drawPanel2, 1, wxEXPAND);
	panel->SetSizer(vbox);

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


BEGIN_EVENT_TABLE(BasicDrawPane, wxPanel)
// some useful events
/*
EVT_MOTION(BasicDrawPane::mouseMoved)
EVT_LEFT_DOWN(BasicDrawPane::mouseDown)
EVT_LEFT_UP(BasicDrawPane::mouseReleased)
EVT_RIGHT_DOWN(BasicDrawPane::rightClick)
EVT_LEAVE_WINDOW(BasicDrawPane::mouseLeftWindow)
EVT_KEY_DOWN(BasicDrawPane::keyPressed)
EVT_KEY_UP(BasicDrawPane::keyReleased)
EVT_MOUSEWHEEL(BasicDrawPane::mouseWheelMoved)
*/
// catch paint events
EVT_PAINT(BasicDrawPane::paintEvent)
END_EVENT_TABLE()

BasicDrawPane::BasicDrawPane(wxFrame* parent) :
wxPanel(parent)
{
}

void BasicDrawPane::paintEvent(wxPaintEvent & evt)
{
	wxPaintDC dc(this);
	render(dc);
}

void BasicDrawPane::paintNow()
{
	wxClientDC dc(this);
	render(dc);
}

void BasicDrawPane::render(wxDC&  dc)
{
	///// draw some text
	//dc.DrawText(wxT("Testing"), 40, 60);

	//// draw a circle
	//dc.SetBrush(*wxGREEN_BRUSH); // green filling
	//dc.SetPen(wxPen(wxColor(255, 0, 0), 5)); // 5-pixels-thick red outline
	//dc.DrawCircle(wxPoint(200, 100), 25 /* radius */);

	//// draw a rectangle
	//dc.SetBrush(*wxBLUE_BRUSH); // blue filling
	//dc.SetPen(wxPen(wxColor(255, 175, 175), 10)); // 10-pixels-thick pink outline
	//dc.DrawRectangle(300, 100, 400, 200);

	//// draw a line
	//dc.SetPen(wxPen(wxColor(0, 0, 0), 3)); // black line, 3 pixels thick
	//dc.DrawLine(300, 100, 700, 300); // draw line across the rectangle

	dc.DrawLine(5, 5, 35, 35);
	dc.DrawLine(35, 5, 5, 35);

	dc.SetBrush(*wxTRANSPARENT_BRUSH);
	dc.DrawCircle(20, 20, 15 /* radius */);

	dc.DrawRectangle(0, 0, 40, 40);
}