#include "App.h"
#include "MainFrame.h"

bool App::OnInit() {
	MainFrame* frame = new MainFrame("Tram Simulator");
	frame->Show(true);
	return true;
}