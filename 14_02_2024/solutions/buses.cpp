#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;

// Функция для вывода списка маршрутов через пробел
void PrintBusesForStop(const map<string, vector<string>>& stops_to_buses, const string& stop) {
    if (stops_to_buses.count(stop) == 0) {
        cout << "No stop" << endl;
    } else {
        for (const string& bus : stops_to_buses.at(stop)) {
            cout << bus << " ";
        }
        cout << endl;
    }
}

// Функция для вывода списка остановок и маршрутов на них
void PrintStopsForBus(const map<string, vector<string>>& buses_to_stops, const map<string, vector<string>>& stops_to_buses, const string& bus) {
    if (buses_to_stops.count(bus) == 0) {
        cout << "No bus" << endl;
    } else {
        for (const string& stop : buses_to_stops.at(bus)) {
            cout << "Stop " << stop << ": ";
            if (stops_to_buses.at(stop).size() == 1) {
                cout << "no interchange";
            } else {
                for (const string& other_bus : stops_to_buses.at(stop)) {
                    if (bus != other_bus) {
                        cout << other_bus << " ";
                    }
                }
            }
            cout << endl;
        }
    }
}

// Функция для вывода всех маршрутов с их остановками
void PrintAllBuses(const map<string, vector<string>>& buses_to_stops) {
    if (buses_to_stops.empty()) {
        cout << "No buses" << endl;
    } else {
        for (const auto& bus_item : buses_to_stops) {
            cout << "Bus " << bus_item.first << ": ";
            for (const string& stop : bus_item.second) {
                cout << stop << " ";
            }
            cout << endl;
        }
    }
}

int main() {
    int q;
    cin >> q;

    map<string, vector<string>> buses_to_stops, stops_to_buses;

    for (int i = 0; i < q; ++i) {
        string operation;
        cin >> operation;

        if (operation == "NEW_BUS") {
            string bus;
            int stop_count;
            cin >> bus >> stop_count;
            vector<string>& stops = buses_to_stops[bus];
            stops.resize(stop_count);
            for (string& stop : stops) {
                cin >> stop;
                stops_to_buses[stop].push_back(bus);
            }
        } else if (operation == "BUSES_FOR_STOP") {
            string stop;
            cin >> stop;
            PrintBusesForStop(stops_to_buses, stop);
        } else if (operation == "STOPS_FOR_BUS") {
            string bus;
            cin >> bus;
            PrintStopsForBus(buses_to_stops, stops_to_buses, bus);
        } else if (operation == "ALL_BUSES") {
            PrintAllBuses(buses_to_stops);
        }
    }

    return 0;
}
