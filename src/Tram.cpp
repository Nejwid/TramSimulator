#include "Tram.h"
#include "TramModels.h"
#include "TramStop.h"

Tram::Tram(int nr) : isOnRoute(false), tramID(nr) {}

void Tram::SetRoute(queue<pair<shared_ptr<TramStop>, int>> rozk³ad) { // ustawienie linii i godziny odjazdu
	if (!isOnRoute) {	
		this->remainingStops = rozk³ad;
		this->isOnRoute = true;
	} 
}

bool Tram::PassengerExchange() { // obs³ugujemy przystanek przez czas zale¿ny od modelu tramwaju
	this_thread::sleep_for(chrono::milliseconds(this->timeAtStop*10)); 
	return true;
}

void Tram::Move() { // jedziemy do nastepnego przystanku przez czas podany w rozk³adzie jazdy
	this_thread::sleep_for(chrono::milliseconds(this->remainingStops.front().second*100));
}


void Tram::OpenDoors() { // dojechaliœmy do nastêpnego przystanku
	
	remainingStops.front().first->MakeAStop(this->timeAtStop);
	
	remainingStops.pop();
}

chrono::milliseconds Tram::RouteRuntime() { // pomiar czasu przejazdu
	this->startMeasuring = chrono::steady_clock::now();

	while (!remainingStops.empty()) {
		this->Move();
		this->OpenDoors();
	}

	this->endMeasuring = chrono::steady_clock::now();

	auto ca³kowityCzas = chrono::duration_cast<chrono::milliseconds>(this->endMeasuring - this->startMeasuring);

	return ca³kowityCzas;
}

void Tram::Delay(int opóŸnienie) { 
	this_thread::sleep_for(chrono::milliseconds(opóŸnienie*10));
}
