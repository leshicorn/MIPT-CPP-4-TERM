#include "query.h"
#include <iostream>

std::istream& operator>>(std::istream& is, Query& q) {
    int stops_count;
    std::string operation;
    is >> operation;
    if (operation == "NEW_BUS") {
        q.type = QueryType::NewBus;
        is >> q.bus >> stops_count;
        q.stops.resize(stops_count);
        for (std::string& stop : q.stops) {
            is >> stop;
        }
    } else if (operation == "BUSES_FOR_STOP") {
        q.type = QueryType::BusesForStop;
        is >> q.stop;
    } else if (operation == "STOPS_FOR_BUS") {
        q.type = QueryType::StopsForBus;
        is >> q.bus;
    } else if (operation == "ALL_BUSES") {
        q.type = QueryType::AllBuses;
    }
    return is;
}
