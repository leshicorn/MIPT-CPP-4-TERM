#include "responses.h"

std::ostream& operator<<(std::ostream& os, const BusesForStopResponse& r) {
    if (r.buses.empty()) {
        os << "No stop";
    } else {
        for (const std::string& bus : r.buses) {
            os << bus << " ";
        }
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const StopsForBusResponse& r) {
    if (r.stops.empty()) {
        os << "No bus";
    } else {
        for (const auto& stop_item : r.stops) {
            os << "Stop " << stop_item.first << ": ";
            if (stop_item.second.empty()) {
                os << "no interchange";
            } else {
                for (const std::string& other_bus : stop_item.second) {
                    os << other_bus << " ";
                }
            }
            os << std::endl;
        }
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const AllBusesResponse& r) {
    if (r.buses.empty()) {
        os << "No buses";
    } else {
        for (const auto& bus_item : r.buses) {
            os << "Bus " << bus_item.first << ": ";
            for (const std::string& stop : bus_item.second) {
                os << stop << " ";
            }
            os << std::endl;
        }
    }
    return os;
}
