#include "Frame.h"

wxBEGIN_EVENT_TABLE(TTTFrame, wxFrame)
EVT_MENU(wxID_EXIT, TTTFrame::OnExit)
wxEND_EVENT_TABLE()

TTTFrame::TTTFrame(const wxString& title)
: wxFrame(NULL, -1, title, wxDefaultPosition, wxSize(300, 325))
{
	wxPanel *panel = new wxPanel(this, -1);
	wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
	wxGridSizer *gridBox = new wxGridSizer(3, 3, 2, 2);

	wxStaticText *topBar = new wxStaticText(panel, -1, wxT("Welcome to Tic Tac Toe"));

	BasicDrawPane *drawPanel1 = new BasicDrawPane(panel, true);
	BasicDrawPane *drawPanel2 = new BasicDrawPane(panel, false);
	BasicDrawPane *drawPanel3 = new BasicDrawPane(panel, true);
	BasicDrawPane *drawPanel4 = new BasicDrawPane(panel, false);
	BasicDrawPane *drawPanel5 = new BasicDrawPane(panel, true);
	BasicDrawPane *drawPanel6 = new BasicDrawPane(panel, false);
	BasicDrawPane *drawPanel7 = new BasicDrawPane(panel, true);
	BasicDrawPane *drawPanel8 = new BasicDrawPane(panel, false);
	BasicDrawPane *drawPanel9 = new BasicDrawPane(panel, true);
	
	vbox->Add(topBar, 0, wxEXPAND);
	vbox->Add(gridBox, 0, wxALIGN_CENTER);

	gridBox->Add(drawPanel1, 0);
	gridBox->Add(drawPanel2, 0);
	gridBox->Add(drawPanel3, 0);
	gridBox->Add(drawPanel4, 0);
	gridBox->Add(drawPanel5, 0);
	gridBox->Add(drawPanel6, 0);
	gridBox->Add(drawPanel7, 0);
	gridBox->Add(drawPanel8, 0);
	gridBox->Add(drawPanel9, 0);
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


wxBEGIN_EVENT_TABLE(BasicDrawPane, wxPanel)
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
wxEND_EVENT_TABLE()

BasicDrawPane::BasicDrawPane(wxPanel* parent, bool cross) :
wxPanel(parent, -1, wxDefaultPosition, wxSize(80, 80)), cross(cross)
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

	int width, heigth;

	DoGetClientSize(&width, &heigth);

	dc.SetBrush(*wxTRANSPARENT_BRUSH);	
	if (cross){
		dc.DrawLine(5, 5, width - 5, heigth - 5);
		dc.DrawLine(width - 5, 5, 5, heigth - 5);
	}
	else
	{
		dc.DrawCircle(width / 2, heigth / 2, width / 2 - 5 /* radius */);
	}
	dc.DrawRectangle(0, 0, width, width);
}