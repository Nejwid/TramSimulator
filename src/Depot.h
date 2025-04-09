#pragma once
#include "TramModels.h"
#include <memory>
#include <iostream>

using namespace std;

class Depot {
public:
	virtual unique_ptr<Tram> TramNumberOne(int id) = 0;
	virtual unique_ptr<Tram> TramNumberTwo(int id) = 0;
};

class BorekDepot : public Depot {
public:
	unique_ptr<Tram> TramNumberOne(int nr) override;
	unique_ptr<Tram> TramNumberTwo(int nr) override;
};

class GajDepot : public Depot {
public:
	unique_ptr<Tram> TramNumberOne(int nr) override;
	unique_ptr<Tram> TramNumberTwo(int nr) override;
};

class O³binDepot : public Depot {
public:
	unique_ptr<Tram> TramNumberOne(int nr) override;
	unique_ptr<Tram> TramNumberTwo(int nr) override;
};