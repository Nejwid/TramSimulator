#pragma once
#include <queue>
#include <memory>
#include <mutex>
#include <future>
#include <list>
#include <iostream>

class Tram;

using namespace::std;

class TramStop {

protected:

	string name;

	mutex mtx;

public:

	TramStop();

	TramStop(const string& nazwa);

	void MakeAStop(int czas); // parameter is trams specific time of passenger exchange

	string GetName() const;
};

