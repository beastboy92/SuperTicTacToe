#include "BasicDrawPanel.h"
#include "TTTFrame.h"

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
EVT_LEFT_UP(BasicDrawPanel::mouseReleased)
wxEND_EVENT_TABLE()

BasicDrawPanel::BasicDrawPanel(wxPanel* parent, SuperTTT* t, int panel) :
wxPanel(parent, -1, wxDefaultPosition, wxSize(80, 80)), cross(false), click(false), t(t), panel(panel)
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
	int row = panel / 3;
	int column = panel % 3;
	if (!(t->isAWin(SuperTTT::COMPUTER) || t->isAWin(SuperTTT::HUMAN))){
		if (t->giveLastPlayer() == SuperTTT::HUMAN){
			if (t->playMove(SuperTTT::COMPUTER, row, column)){
				click = true;
				cross = true;
				paintNow();
				t->setLastPlayer(SuperTTT::COMPUTER);
			}
		}
		else if (t->giveLastPlayer() == SuperTTT::COMPUTER){
			if (t->playMove(SuperTTT::HUMAN, row, column)){
				click = true;
				paintNow();
				t->setLastPlayer(SuperTTT::HUMAN);
			}
		}
	}	
}

void BasicDrawPanel::mouseReleased(wxMouseEvent& event){
	TTTFrame *frame = static_cast < TTTFrame *>(this->GetParent()->GetParent());

	if (t->isAWin(SuperTTT::COMPUTER)) {
		frame->topBar->SetLabel(wxT("Computer wins!!"));
	}
	else if (t->isAWin(SuperTTT::HUMAN)) {
		frame->topBar->SetLabel(wxT("Human wins!!"));
	}
	else if (t->boardIsFull()) {
		frame->topBar->SetLabel(wxT("Draw!!"));
	}
}

void BasicDrawPanel::render(wxDC&  dc)
{
	/*/// draw some text
	dc.DrawText(wxT("Testing"), 40, 60);

	// draw a circle
	dc.SetBrush(*wxGREEN_BRUSH); // green filling
	dc.SetPen(wxPen(wxColor(255, 0, 0), 5)); // 5-pixels-thick red outline
	dc.DrawCircle(wxPoint(200, 100), 25);

	// draw a rectangle
	dc.SetBrush(*wxBLUE_BRUSH); // blue filling
	dc.SetPen(wxPen(wxColor(255, 175, 175), 10)); // 10-pixels-thick pink outline
	dc.DrawRectangle(300, 100, 400, 200);

	// draw a line
	dc.SetPen(wxPen(wxColor(0, 0, 0), 3)); // black line, 3 pixels thick
	dc.DrawLine(300, 100, 700, 300); // draw line across the rectangle*/

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
