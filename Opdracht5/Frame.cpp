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

	/*BasicDrawPanel *drawPanel1 = new BasicDrawPanel(panel, true);
	BasicDrawPanel *drawPanel2 = new BasicDrawPanel(panel, false);
	BasicDrawPanel *drawPanel3 = new BasicDrawPanel(panel, true);
	BasicDrawPanel *drawPanel4 = new BasicDrawPanel(panel, false);
	BasicDrawPanel *drawPanel5 = new BasicDrawPanel(panel, true);
	BasicDrawPanel *drawPanel6 = new BasicDrawPanel(panel, false);
	BasicDrawPanel *drawPanel7 = new BasicDrawPanel(panel, true);
	BasicDrawPanel *drawPanel8 = new BasicDrawPanel(panel, false);
	BasicDrawPanel *drawPanel9 = new BasicDrawPanel(panel, true);*/

	for (int row = 0; row < 3; ++row) {
		for (int column = 0; column < 3; ++column)
		{
			drawPanel(row, column) = new BasicDrawPanel(panel, true);
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


wxBEGIN_EVENT_TABLE(BasicDrawPanel, wxPanel)
// some useful events
/*
EVT_MOTION(BasicDrawPanel::mouseMoved)
EVT_LEFT_DOWN(BasicDrawPanel::mouseDown)
EVT_LEFT_UP(BasicDrawPanel::mouseReleased)
EVT_RIGHT_DOWN(BasicDrawPanel::rightClick)
EVT_LEAVE_WINDOW(BasicDrawPanel::mouseLeftWindow)
EVT_KEY_DOWN(BasicDrawPanel::keyPressed)
EVT_KEY_UP(BasicDrawPanel::keyReleased)
EVT_MOUSEWHEEL(BasicDrawPanel::mouseWheelMoved)
*/
// catch paint events
EVT_PAINT(BasicDrawPanel::paintEvent)
EVT_LEFT_DOWN(BasicDrawPanel::mouseDown)
wxEND_EVENT_TABLE()

BasicDrawPanel::BasicDrawPanel(wxPanel* parent, bool cross) :
wxPanel(parent, -1, wxDefaultPosition, wxSize(80, 80)), cross(cross), click(false)
{
}

void BasicDrawPanel::paintEvent(wxPaintEvent & evt)
{
	wxPaintDC dc(this);
	render(dc);
}

void BasicDrawPanel::paintNow()
{
	wxClientDC dc(this);
	render(dc);
}

void BasicDrawPanel::mouseDown(wxMouseEvent& event)
{
	click = true;
	paintNow();
}

void BasicDrawPanel::render(wxDC&  dc)
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
	//dc.SetBrush(*wxRED_BRUSH);
	dc.DrawRectangle(0, 0, width, width);
	if (click){
		if (cross){
			dc.DrawLine(5, 5, width - 5, heigth - 5);
			dc.DrawLine(width - 5, 5, 5, heigth - 5);
		}
		else
		{
			dc.DrawCircle(width / 2, heigth / 2, width / 2 - 5 /* radius */);
		}
	}	
}