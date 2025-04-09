#pragma once
#include <unordered_map>
#include <vector>
#include <chrono>
#include <mutex>
#include <queue>
#include <future>
#include "Timetable.h"

class Tram;
class TramStop;
class Depot;

using namespace::std;

class TrafficManager { // singleton  
private:

	TrafficManager();
	
	static mutex mtx;
	
	static unique_ptr<TrafficManager> instance;

	TrafficManager(const TrafficManager&) = delete;

	TrafficManager& operator=(const TrafficManager&) = delete;

	unique_ptr<Timetables> timetable;

	unordered_map<int, vector<shared_ptr<Tram>>> simulationInfo; // przypisanie tramwajów do linii

	unordered_map<shared_ptr<Tram>, chrono::milliseconds> runtime; // czas przejazdu tramwaju 

	unordered_map<string, queue<pair<shared_ptr<TramStop>, int>>> GUI_lines; // powi¹zanie danych z GUI z rozk³adem jazdy

	vector<thread> tramTraffic; // ruch 

	promise<void> start; // mechanizm do równoczesnego uruchomienia wszystkich w¹tków

	shared_future<void> startSimulation; // shared future pozwala wielu w¹tkom pobrac stan promise

	void StartRoute(shared_ptr<Tram> tramwaj, int czasOdjazdu, shared_future<void> future);

	void CreateRoute(shared_ptr<Tram> tram, int numerLinii, queue<pair<shared_ptr<TramStop>, int>> rozk³ad, int czasOdjazdu);

	void GUI_Linie();

	unique_ptr<Depot> Borek, Gaj, O³bin;

	int virtualTramID; // dla rozroznienia tramwajow w GUI

public:

	static TrafficManager* GetInstance();

	void Setup();

	void GUI_Setup(const string&tramwaj, const string&linia, int odjazd);

	void RunSimulation();

	vector<string> Stats();
};

