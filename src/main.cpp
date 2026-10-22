#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include "airport.h"
#include "airportBST.h"

using namespace std;

vector<Airport*> LoadFile(ifstream& file) {
    vector<Airport*> airports;
    string line;

    while (getline(file, line)) {
        vector<string> fields;
        string item = "";
        bool inQuotes = false;

        for (int i = 0; i < line.length(); i++) {
            char ch = line[i];

            if (ch == '"') {
                if (inQuotes && i + 1 < line.length() && line[i+1] == '"') {
                    item += '"';
                    i++;
                } else {
                    inQuotes = !inQuotes;
                }
            } else if (ch == ',' && !inQuotes) {
                fields.push_back(item);
            } else {
                item += ch;
            }
        }
        fields.push_back(item); 

        string iata = fields[4];
        if (iata != "\\N") {
            string name = fields[1];
            string city = fields[2];
            string country = fields[3];
            string icao = fields[5];
            double lat = stod(fields[6]);
            double lon = stod(fields[7]);
            Airport newAirport = Airport(name, city, country, iata, icao, lat, lon);
            airports.push_back(&newAirport);
        }
    }

    return airports;
}

AirportBST BuildTree(vector<Airport*> airports) {
    int n = airports.size();
    int added = 0;
    int duplicates = 0;

    AirportBST AirportTree = AirportBST();

    for (int i = 0; i < n; i++) {
        if (AirportTree.Insert(airports[i]) == "Added") {
            added++;
        } else {
            duplicates++;
        }
    }

    int height = AirportTree.GetHeight();
    int avgDepth = AirportTree.AvgHeight();

    cout << "Loaded: " << added << " airports, Duplicates: " << duplicates << endl;
    cout << "Height: " << height << "\t Average Depth: " << avgDepth << endl;

    return AirportTree;
}