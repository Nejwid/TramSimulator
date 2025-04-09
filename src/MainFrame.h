#pragma once
#include <wx/wx.h>
#include <wx/listbox.h>
#include <vector>

class TrafficManager;

using namespace ::std;

enum IDs {
	TRAM_SETUP_ID = 0,
	LINE_SETUP_ID = 1,
	START_SIMULATION_ID = 2,
	WYBIERZ_TRAMWAJ_ID = 3,
	WYBIERZ_CZAS_ID = 4,
	DODAJ_TRAMWAJ_ID = 5,
	SHOW_SETUP_ID = 6,
	CONFIG_RESET_ID = 7,
	USTAW_CZAS_ID = 8,
	WYNIKI_ID = 9,
};

class MainFrame : public wxFrame {
private:
	TrafficManager* OnDuty;

	vector<string> trams, lines;
	vector<int> departures;

	wxPanel* panel;

	wxStaticBitmap* bckground;
	wxStaticText* text;

	wxButton* config;
	wxButton* configReset;
	wxButton* addTram;
	wxButton* setTime;
	wxButton* startSimulation;

	wxTextCtrl* departureTime;

	wxListBox* tramChoose;
	wxListBox* lineChoose;
	wxListBox* configSetup;
	wxListBox* simulationResult;

	wxString currentTram, currentLine;
	long currentTime;

	void TramModels();
	void TramLines();

	void ConfigReset(wxCommandEvent& event);
	void AddElements(wxCommandEvent& event);

	void TramChoose(wxCommandEvent& event);
	void LineChoose(wxCommandEvent& event);
	void TimeChoose(wxCommandEvent& event);

	void StartSimulation(wxCommandEvent& event);
	void GetResults();

	void LoadBckground(const string&nazwa);

public:
	MainFrame(const wxString& title);

	wxDECLARE_EVENT_TABLE();
};