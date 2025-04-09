#include "TramStop.h"
#include "Tram.h"

TramStop::TramStop() : name("") {}

TramStop::TramStop(const string&nazwa) : name(nazwa) {}

void TramStop::MakeAStop(int czas) { // blokujemy inne w�tki mutexem symuluj�c op�nienia
	lock_guard<mutex> lock(mtx); 
	this_thread::sleep_for(chrono::milliseconds(10 * czas));
}

string TramStop::GetName() const { // getter
	return this->name;
}

