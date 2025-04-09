#include "TrafficManager.h"
#include "Depot.h"
#include "Timetable.h"

// funkcja gdzie przypisujemy tramwaje i linie, godziny odjazdu

void TrafficManager::GUI_Linie() {
	GUI_lines = { 
		{"2",timetable->Linia_2()},
		{"4", timetable->Linia_4()},
		{"5", timetable->Linia_5()},
		{"10", timetable->Linia_10()},
		{"11", timetable->Linia_11()},
		{"12", timetable->Linia_12()},
		{"17", timetable->Linia_17()},
		{"21", timetable->Linia_21()},
		{"22", timetable->Linia_22()}
	};
}

void TrafficManager::Setup() {

	shared_ptr<Tram> Gamma_1 = Borek->TramNumberTwo(3302);
	shared_ptr<Tram> Gamma_2 = Borek->TramNumberTwo(3301);
	shared_ptr<Tram> Gamma_3 = Borek->TramNumberTwo(3303);
	shared_ptr<Tram> Beta_1 = Gaj->TramNumberTwo(2917);
	shared_ptr<Tram> Beta_2 = Gaj->TramNumberTwo(2933);
	shared_ptr<Tram> Konstal = O³bin->TramNumberOne(2239);

	this->CreateRoute(Beta_1, 21, timetable->Linia_21(), 15);
	this->CreateRoute(Beta_2, 11, timetable->Linia_11(), 20);
	this->CreateRoute(Konstal, 4, timetable->Linia_4(), 0);
	this->CreateRoute(Gamma_1, 10, timetable->Linia_10(), 0);
	this->CreateRoute(Gamma_2, 10, timetable->Linia_10(), 50);
	this->CreateRoute(Gamma_3, 10, timetable->Linia_10(), 100); 
}

void TrafficManager::GUI_Setup(const string& tramwaj, const string& linia, int odjazd) {

	this->virtualTramID++;

	shared_ptr<Tram> tram;

	if (tramwaj == "Moderus Beta MF 24 AC") tram = Gaj->TramNumberTwo(virtualTramID);
	else if (tramwaj == "Moderus Gamma LF 07 AC") tram = Borek->TramNumberTwo(virtualTramID);
	else if (tramwaj == "Pesa Twist 2010 Nw") tram = Gaj->TramNumberOne(virtualTramID);
	else if (tramwaj == "Pesa Twist 146n") tram = Borek->TramNumberOne(virtualTramID);
	else if (tramwaj == "Konstal 105 Na") tram = O³bin->TramNumberOne(virtualTramID);
	else if (tramwaj == "Protram 105 NWr") tram = O³bin->TramNumberTwo(virtualTramID);
	
	this->CreateRoute(tram, stoi(linia), GUI_lines[linia], odjazd);
}