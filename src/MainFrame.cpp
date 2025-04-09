#include "MainFrame.h"
#include "TrafficManager.h"

void MainFrame::TramModels() {
	tramChoose->Append("Moderus Beta MF 24 AC");
	tramChoose->Append("Moderus Gamma LF 07 AC");
	tramChoose->Append("Pesa Twist 2010 Nw");
	tramChoose->Append("Pesa Twist 146n");
	tramChoose->Append("Konstal 105 Na");
	tramChoose->Append("Protram 105 NWr");
}

void MainFrame::TramLines() {
	lineChoose->Append("2");
	lineChoose->Append("4");
	lineChoose->Append("5");
	lineChoose->Append("10");
	lineChoose->Append("11");
	lineChoose->Append("12");
	lineChoose->Append("17");
	lineChoose->Append("21");
	lineChoose->Append("22");
}

void MainFrame::TramChoose(wxCommandEvent& event) {
	int index = event.GetSelection();
	if (index != wxNOT_FOUND) {
		currentTram = event.GetString();
	}
	wxLogStatus(currentTram);
	return;
}

void MainFrame::LineChoose(wxCommandEvent& event) {
	int index = event.GetSelection();
	if (index != wxNOT_FOUND) {
		currentLine = event.GetString();
	}
	wxLogStatus(currentLine);
	return;
}

void MainFrame::TimeChoose(wxCommandEvent& event) {
	long temp = -1;
	departureTime->GetValue().ToLong(&temp); // konwersja string na long int 
	if (temp >= 0 && temp <= 60) currentTime = temp; // sprawdzenie czy miesci sie w godzine bo tyle maks trwa symulacja
	wxLogStatus(wxString::Format("%ld", currentTime) + " minut(y)");
	return;
}

void MainFrame::AddElements(wxCommandEvent& event) {
	if(currentLine != "" && currentTram != "" && currentTime != INT_MIN)
	configSetup->Append(currentTram + ", linia " + currentLine + ", odjazd +" + wxString::Format("%ld", currentTime) + " minut(y)");
	configSetup->Refresh();
	trams.push_back(string(currentTram.ToStdString()));
	lines.push_back(currentLine.ToStdString());
	departures.push_back(static_cast<int>(currentTime));
	currentTime = INT_MIN;
}

void MainFrame::ConfigReset(wxCommandEvent& event) {
	configSetup->Clear();
	trams.clear();
	lines.clear();
	departures.clear();
}

void MainFrame::StartSimulation(wxCommandEvent& event) {

	tramChoose->Hide();
	lineChoose->Hide();
	addTram->Hide();
	configReset->Hide();
	startSimulation->Hide();
	configSetup->Hide();
	departureTime->Hide();
	setTime->Hide();

	text = new wxStaticText(panel, wxID_ANY, "symulacja w toku", wxPoint(200,200));
	wxFont font(18, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
	text->SetFont(font);
	text->Show();
	wxYield(); // wymuszanie wyœwieltenia static textu

	Layout();

	for (int i = 0; i < trams.size(); i++) {
		OnDuty->GUI_Setup(trams[i], lines[i], departures[i]);
	}
	OnDuty->RunSimulation(); // celowo ta funkcja blokuje nam g³ówny w¹tek ¿eby by³o widaæ ¿e trwa symulacja
	
	text->Hide();
	this->GetResults();
	simulationResult->Show();

	Layout();
}

void MainFrame::GetResults() {
	vector<string> wyniki = OnDuty->Stats();
	for (string& it : wyniki) {
		simulationResult->Append(it);
	}
}

void MainFrame::LoadBckground(const string& nazwa) {
	wxInitAllImageHandlers();
	wxBitmap bitmap(nazwa, wxBITMAP_TYPE_PNG);
	if (bitmap.IsOk()) {
		bckground = new wxStaticBitmap(panel, wxID_ANY, bitmap);
		bckground->SetPosition(wxPoint(800, 100));

	}
}





MainFrame::MainFrame(const wxString& title) :wxFrame(nullptr, wxID_ANY, title) {

	OnDuty = TrafficManager::GetInstance();
	
	currentLine = ""; currentTram = ""; currentTime = INT_MIN;
	
	panel = new wxPanel(this, wxID_ANY);

	this->LoadBckground("Konstal105Na_bitmap.png");

	CreateStatusBar();

	tramChoose = new wxListBox(panel, TRAM_SETUP_ID, wxPoint(100, 100), wxSize(150, 100), 0, nullptr, wxLB_SINGLE);
	this->TramModels();
	lineChoose = new wxListBox(panel, LINE_SETUP_ID, wxPoint(260, 100), wxSize(50, 100), 0, nullptr, wxLB_SINGLE);
	this->TramLines();

	addTram = new wxButton(panel, DODAJ_TRAMWAJ_ID, "dodaj do symulacji", wxPoint(155, 220), wxSize(120, 50));

	configReset = new wxButton(panel, CONFIG_RESET_ID, "reset", wxPoint(155, 280), wxSize(120, 50));

	startSimulation = new wxButton(panel, START_SIMULATION_ID, "rozpocznij symulacje", wxPoint(155, 340), wxSize(120, 50));

	configSetup = new wxListBox(panel, SHOW_SETUP_ID, wxPoint(430, 100), wxSize(300, 100));

	departureTime = new wxTextCtrl(panel, WYBIERZ_CZAS_ID, "", wxPoint(355, 170), wxSize(30, 30));

	setTime = new wxButton(panel, USTAW_CZAS_ID, "ustaw czas", wxPoint(320, 220), wxSize(100, 30));

	simulationResult = new wxListBox(panel, WYNIKI_ID, wxPoint(260, 100), wxSize(350, 300));
	simulationResult->Hide();

}

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
EVT_LISTBOX(TRAM_SETUP_ID, MainFrame::TramChoose)
EVT_LISTBOX(LINE_SETUP_ID, MainFrame::LineChoose)
EVT_BUTTON(DODAJ_TRAMWAJ_ID, MainFrame::AddElements)
EVT_BUTTON(CONFIG_RESET_ID, MainFrame::ConfigReset)
EVT_BUTTON(USTAW_CZAS_ID, MainFrame::TimeChoose)
EVT_BUTTON(START_SIMULATION_ID, MainFrame::StartSimulation)
wxEND_EVENT_TABLE()