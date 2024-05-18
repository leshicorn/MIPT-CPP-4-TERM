#include "bus_manager.h"

void BusManager::AddBus(const std::string& bus, const std::vector<std::string>& stops) {
    for (const std::string& stop : stops) {
        buses_to_stops[bus].push_back(stop);
        stops_to_buses[stop].push_back(bus);
    }
}

BusesForStopResponse BusManager::GetBusesForStop(const std::string& stop) const {
    if (stops_to_buses.count(stop) == 0) {
        return {};
    } else {
        return {stops_to_buses.at(stop)};
    }
}

StopsForBusResponse BusManager::GetStopsForBus(const std::string& bus) const {
    if (buses_to_stops.count(bus) == 0) {
        return {};
    } else {
        StopsForBusResponse result;
        result.bus = bus;
        for (const std::string& stop : buses_to_stops.at(bus)) {
            std::vector<std::string> buses;
            for (const std::string& other_bus : stops_to_buses.at(stop)) {
                if (other_bus != bus) {
                    buses.push_back(other_bus);
                }
            }
            result.stops.push_back({stop, buses});
        }
        return result;
    }
}

AllBusesResponse BusManager::GetAllBuses() const {
    return {buses_to_stops};
}
