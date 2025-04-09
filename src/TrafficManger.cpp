#include "TrafficManager.h"
#include "Tram.h"
#include "TramStop.h"
#include "Timetable.h"
#include "Depot.h"

mutex TrafficManager::mtx;

unique_ptr<TrafficManager> TrafficManager::instance = nullptr;

TrafficManager* TrafficManager::GetInstance() { //  singleton
    
    std::lock_guard<std::mutex> lock(mtx);
    
    instance.reset(new TrafficManager);
 
    return instance.get(); //returns raw pointer
}

TrafficManager::TrafficManager() : timetable(make_unique<Timetables>()), startSimulation(start.get_future().share()) { 
    
    this->GUI_Linie(); 
    
    this->virtualTramID = 0;
    
    this->Borek = make_unique<BorekDepot>();
    
    this->Gaj = make_unique<GajDepot>();
   
    this->O³bin = make_unique<O³binDepot>();
} 

void TrafficManager::StartRoute(shared_ptr<Tram> tramwaj, int czasOdjazdu, shared_future<void> future) { // I use future to make sure all threads start at the same time 
    
    future.get();
    
    this_thread::sleep_for(chrono::milliseconds(czasOdjazdu * 10)); // 
    
    this->runtime[tramwaj] = tramwaj->RouteRuntime();
}

void TrafficManager::CreateRoute(shared_ptr<Tram> tramwaj, int numerLinii, queue<pair<shared_ptr<TramStop>, int>> rozk³ad, int czasOdjazdu) { 

    this->simulationInfo[numerLinii].push_back(tramwaj); 

    tramwaj->SetRoute(rozk³ad);

    this->tramTraffic.push_back(thread(&TrafficManager::StartRoute, this, tramwaj, czasOdjazdu, ref(this->startSimulation))); // route thread
}

void TrafficManager::RunSimulation() {
    
    this->start.set_value(); // start all threads
   
    for (auto& kurs : tramTraffic) {
        
        kurs.join(); // check if every thread ended
    }
}

vector<string> TrafficManager::Stats() { 
   
    vector<string> dane;
    
    for (auto& it : simulationInfo) {
        
        for (auto& tramwaj : it.second) {
            
            string temp = tramwaj->TramModel() + " linia " + to_string(it.first) + " czas przejazdu " + to_string(runtime[tramwaj].count());
            
            dane.push_back(temp);
        }
    }
   
    return dane;
}


