#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

enum class QueryType {
  NewBus,
  BusesForStop,
  StopsForBus,
  AllBuses
};

struct Query {
  QueryType type;
  string bus;
  string stop;
  vector<string> stops;
};

istream& operator >> (istream& is, Query& q) {
  int stops_count;
  string operation;
  is >> operation;
  if (operation == "NEW_BUS") {
    q.type = QueryType::NewBus;
    is >> q.bus >> stops_count;
    q.stops.resize(stops_count);
    for (string& stop : q.stops) {
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

struct BusesForStopResponse {
  vector<string> buses;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
  if (r.buses.empty()) {
    os << "No stop";
  } else {
    for (const string& bus : r.buses) {
      os << bus << " ";
    }
  }
  return os;
}

struct StopsForBusResponse {
  string bus;
  vector<pair<string, vector<string>>> stops;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
  if (r.stops.empty()) {
    os << "No bus";
  } else {
    for (const auto& stop_item : r.stops) {
      os << "Stop " << stop_item.first << ": ";
      if (stop_item.second.empty()) {
        os << "no interchange";
      } else {
        for (const string& other_bus : stop_item.second) {
          os << other_bus << " ";
        }
      }
      os << endl;
    }
  }
  return os;
}

struct AllBusesResponse {
  map<string, vector<string>> buses;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
  if (r.buses.empty()) {
    os << "No buses";
  } else {
    for (const auto& bus_item : r.buses) {
      os << "Bus " << bus_item.first << ": ";
      for (const string& stop : bus_item.second) {
        os << stop << " ";
      }
      os << endl;
    }
  }
  return os;
}

class BusManager {
public:
  void AddBus(const string& bus, const vector<string>& stops) {
    for (const string& stop : stops) {
      buses_to_stops[bus].push_back(stop);
      stops_to_buses[stop].push_back(bus);
    }
  }

  BusesForStopResponse GetBusesForStop(const string& stop) const {
    if (stops_to_buses.count(stop) == 0) {
      return {};
    } else {
      return {stops_to_buses.at(stop)};
    }
  }

  StopsForBusResponse GetStopsForBus(const string& bus) const {
    if (buses_to_stops.count(bus) == 0) {
      return {};
    } else {
      StopsForBusResponse result;
      result.bus = bus;
      for (const string& stop : buses_to_stops.at(bus)) {
        vector<string> buses;
        for (const string& other_bus : stops_to_buses.at(stop)) {
          if (other_bus != bus) {
            buses.push_back(other_bus);
          }
        }
        result.stops.push_back({stop, buses});
      }
      return result;
    }
  }

  AllBusesResponse GetAllBuses() const {
    return {buses_to_stops};
  }

private:
  map<string, vector<string>> buses_to_stops, stops_to_buses;
};

int main() {
  int query_count;
  Query q;

  cin >> query_count;

  BusManager bm;
  for (int i = 0; i < query_count; ++i) {
    cin >> q;
    switch (q.type) {
    case QueryType::NewBus:
      bm.AddBus(q.bus, q.stops);
      break;
    case QueryType::BusesForStop:
      cout << bm.GetBusesForStop(q.stop) << endl;
      break;
    case QueryType::StopsForBus:
      cout << bm.GetStopsForBus(q.bus) << endl;
      break;
    case QueryType::AllBuses:
      cout << bm.GetAllBuses() << endl;
      break;
    }
  }

  return 0;
}
