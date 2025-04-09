#pragma once
#include <string>
#include <memory>
#include <thread>
#include <chrono> 
#include <queue>

class TramStop;

using namespace::std;

class Tram {

protected:
	
	int tramID;  
	
	int timeAtStop; // different trams have different time
	
	chrono::steady_clock::time_point startMeasuring, endMeasuring; // measuring runtime

	queue<pair<shared_ptr<TramStop>, int>> remainingStops;

	bool isOnRoute;

public:

	Tram(int id);

	void SetRoute(queue<pair<shared_ptr<TramStop>, int>> timetable);

	bool PassengerExchange();

	void OpenDoors();

	void Move();

	void Delay(int opó¿nienie);

	chrono::milliseconds RouteRuntime();

	virtual string TramModel() = 0;
}; 
