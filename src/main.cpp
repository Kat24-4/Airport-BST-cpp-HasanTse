#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>

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
    int avgDepth = AirportTree.AvgDepth();

    cout << "Loaded: " << added << " airports, Duplicates: " << duplicates << endl;
    cout << "Height: " << height << "\t Average Depth: " << avgDepth << endl;

    return AirportTree;
}

string generateRandomCode() {
    const string CHARS =  "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    random_device rd;
    mt19937 generator(rd());

    uniform_int_distribution<> distribution(0, CHARS.size() - 1);

    string randomCode;
    for (int i = 0; i < 3; i++) {
        randomCode += CHARS[distribution(generator)];
    }

    return randomCode; 
}

void ShapeExperiement(ifstream& file) {
    vector<Airport*> airports = LoadFile(file);
    AirportBST firstBST = BuildTree(airports);

    auto start = chrono::high_resolution_clock::now();

    for (int i = 10000; i > 0; i--) {
        firstBST.Find(generateRandomCode());
    }

    auto stop = chrono::high_resolution_clock::now();
    auto fileOrderDuration = chrono::duration_cast<chrono::milliseconds>(stop - start);

    int fileOrderHeight = firstBST.GetHeight();
    int fileOrderAvgDepth = firstBST.AvgDepth();

    cout << "File Order Tree" << endl;
    cout << "===============" << endl; 
    cout << "Height: " << fileOrderHeight << " | Average Depth: " << fileOrderAvgDepth << " |" << endl;
    cout << "Time of 10,000 Searchs: " << fileOrderDuration.count() << endl; 
    cout << endl; 

    sort(airports.begin(), airports.end(), [](const Airport* a, const Airport* b) {
        return a->iataCode < b->iataCode; 
    });

    AirportBST secondBST = AirportBST(); 
    int n = airports.size();
    for (int i = 0; i < n; i++) {
        Airport* currAirport = airports[i];
        Airport toAdd = Airport(currAirport->name, currAirport->city, currAirport->country, currAirport->iataCode, currAirport->icaoCode, currAirport->latitude, currAirport->longitude);
        secondBST.Insert(&toAdd);
    }

    start = chrono::high_resolution_clock::now();

    for (int i = 10000; i > 0; i--) {
        secondBST.Find(generateRandomCode());
    }

    stop = chrono::high_resolution_clock::now();
    auto sortedOrderDuration = chrono::duration_cast<chrono::milliseconds>(stop - start);

    int sortedOrderHeight = secondBST.GetHeight();
    int sortedOrderAvgDepth = secondBST.AvgDepth();

    cout << "Sorted Order Tree" << endl;
    cout << "===============" << endl; 
    cout << "Height: " << sortedOrderHeight << " | Average Depth: " << sortedOrderAvgDepth << " |" << endl;
    cout << "Time of 10,000 Searchs: " << sortedOrderDuration.count() << endl; 
    cout << endl;

    AirportBST thirdBST = AirportBST();
    thirdBST.BuildBalanced(airports, n); 

    start = chrono::high_resolution_clock::now();

    for (int i = 10000; i > 0; i--) {
        thirdBST.Find(generateRandomCode());
    }

    stop = chrono::high_resolution_clock::now();
    auto balancedDuration = chrono::duration_cast<chrono::milliseconds>(stop - start);

    int balancedHeight = thirdBST.GetHeight();
    int balancedAvgDepth = thirdBST.AvgDepth();

    cout << "Sorted Order Tree" << endl;
    cout << "===============" << endl; 
    cout << "Height: " << balancedHeight << " | Average Depth: " << balancedAvgDepth << " |" << endl;
    cout << "Time of 10,000 Searchs: " << balancedDuration.count() << endl; 
}   