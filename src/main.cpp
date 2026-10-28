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
                item = "";
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
            Airport* newAirport = new Airport(name, city, country, iata, icao, lat, lon);
            airports.push_back(newAirport);
        }
    }

    return airports;
}

AirportBST BuildTree(vector<Airport*>& airports) {
    int n = airports.size();
    int added = 0;
    int duplicates = 0;

    AirportBST AirportTree = AirportBST();

    vector<Airport*> unique;
    for (int i = 0; i < n; i++) {
        if (AirportTree.Insert(airports[i]) == "Added") {
            added++;
            unique.push_back(airports[i]);
        } else {
            duplicates++;
            delete airports[i];
        }
    }
    airports = unique;

    int height = AirportTree.GetHeight();
    double avgDepth = AirportTree.AvgDepth();

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
        firstBST.FindNoPrint(generateRandomCode());
    }

    auto stop = chrono::high_resolution_clock::now();
    auto fileOrderDuration = chrono::duration_cast<chrono::milliseconds>(stop - start);

    int fileOrderHeight = firstBST.GetHeight();
    double fileOrderAvgDepth = firstBST.AvgDepth();

    cout << "File Order Tree" << endl;
    cout << "===============" << endl; 
    cout << "Height: " << fileOrderHeight << " | Average Depth: " << fileOrderAvgDepth << " |" << endl;
    cout << "Time of 10,000 Searchs: " << fileOrderDuration.count() << " milliseconds" << endl; 
    cout << endl; 

    sort(airports.begin(), airports.end(), [](const Airport* a, const Airport* b) {
        return a->iataCode < b->iataCode; 
    });

    AirportBST secondBST = AirportBST(); 
    int n = airports.size();
    for (int i = 0; i < n; i++) {
        Airport* currAirport = airports[i];
        Airport* toAdd = new Airport(currAirport->name, currAirport->city, currAirport->country, currAirport->iataCode, currAirport->icaoCode, currAirport->latitude, currAirport->longitude);
        secondBST.Insert(toAdd);
    }

    start = chrono::high_resolution_clock::now();

    for (int i = 10000; i > 0; i--) {
        secondBST.FindNoPrint(generateRandomCode());
    }

    stop = chrono::high_resolution_clock::now();
    auto sortedOrderDuration = chrono::duration_cast<chrono::milliseconds>(stop - start);

    int sortedOrderHeight = secondBST.GetHeight();
    double sortedOrderAvgDepth = secondBST.AvgDepth();

    cout << "Sorted Order Tree" << endl;
    cout << "===============" << endl; 
    cout << "Height: " << sortedOrderHeight << " | Average Depth: " << sortedOrderAvgDepth << " |" << endl;
    cout << "Time of 10,000 Searchs: " << sortedOrderDuration.count() << " milliseconds" << endl; 
    cout << endl;

    AirportBST thirdBST = AirportBST();
    thirdBST.BuildBalanced(airports, n); 

    start = chrono::high_resolution_clock::now();

    for (int i = 10000; i > 0; i--) {
        thirdBST.FindNoPrint(generateRandomCode());
    }

    stop = chrono::high_resolution_clock::now();
    auto balancedDuration = chrono::duration_cast<chrono::milliseconds>(stop - start);

    int balancedHeight = thirdBST.GetHeight();
    double balancedAvgDepth = thirdBST.AvgDepth();

    cout << "Balanced Tree" << endl;
    cout << "===============" << endl; 
    cout << "Height: " << balancedHeight << " | Average Depth: " << balancedAvgDepth << " |" << endl;
    cout << "Time of 10,000 Searchs: " << balancedDuration.count() << " milliseconds" << endl; 
    cout << endl;

    random_device rd;
    mt19937 generator(rd());
    shuffle(airports.begin(), airports.end(), generator);

    AirportBST fourthBST = AirportBST(); 
    n = airports.size();
    for (int i = 0; i < n; i++) {
        Airport* currAirport = airports[i];
        Airport* toAdd = new Airport(currAirport->name, currAirport->city, currAirport->country, currAirport->iataCode, currAirport->icaoCode, currAirport->latitude, currAirport->longitude);
        fourthBST.Insert(toAdd);
    }

    start = chrono::high_resolution_clock::now();

    for (int i = 10000; i > 0; i--) {
        fourthBST.FindNoPrint(generateRandomCode());
    }

    stop = chrono::high_resolution_clock::now();
    auto randomDuration = chrono::duration_cast<chrono::milliseconds>(stop - start);

    int randomHeight = fourthBST.GetHeight();
    double randomAvgDepth = fourthBST.AvgDepth();

    cout << "Random Order Tree" << endl;
    cout << "===============" << endl; 
    cout << "Height: " << randomHeight << " | Average Depth: " << randomAvgDepth << " |" << endl;
    cout << "Time of 10,000 Searchs: " << randomDuration.count() << " milliseconds" << endl; 


    firstBST.Free();
    secondBST.Free();
    thirdBST.Free();
    fourthBST.Free();
}

int main() {
    // Task 1
    ifstream airportFile("data/airports.dat");

    if(!airportFile.is_open()) {
        cerr << "Error opening the file!"; 
        return 1; 
    }

    // vector<Airport*> airports = LoadFile(airportFile);
    // AirportBST aBST = BuildTree(airports); 

    // Task 2
    // aBST.Find("GKA"); // Root
    // aBST.Find("DJJ"); // Leaf
    // aBST.Find("BOS"); // Deep
    // aBST.Find("XYZ"); // Not in tree
    // aBST.Find("AA"); // Smaller than smallest
    // aBST.Find("ZZZ"); // Larger than largest

    // aBST.FindMin();
    // aBST.FindMax(); 

    //Task 3 
    // cout << "--Original Tree--" << endl;
    // aBST.PrintLevelOrder(3);
    // cout << "--Remove Leaf--" << endl;
    // aBST.Remove("DJJ"); 
    // aBST.PrintLevelOrder(3);
    // cout << "--Remove Right Only--" << endl;
    // aBST.Remove("AAA");
    // aBST.PrintLevelOrder(3);
    // cout << "--Remove Left Only--" << endl;
    // aBST.Remove("BOS");
    // aBST.PrintLevelOrder(3);
    // cout << "--Remove Middle Node--" << endl;
    // aBST.Remove("EGS");
    // aBST.PrintLevelOrder(3);
    // cout << "--Remove Root--" << endl;
    // aBST.Remove("GKA");
    // aBST.PrintLevelOrder(3);

    // Airport* newAiport = new Airport("Q Airport", "Q City", "United States of America", "QQQ", "BAQQ", 10.1, 11.1);
    // aBST.Insert(newAiport);
    // aBST.Find("QQQ");
    // cout << "--Remove QQQ--" << endl;
    // aBST.Remove("QQQ");
    // aBST.Find("QQQ");

    // Task 4
    // aBST.List();

    // ofstream outFile("outFile.dat");

    // if (!outFile.is_open()) {
    //     cerr << "Error opening the file!"; 
    //     return 1;
    // }

    // aBST.Save(outFile);

    // outFile.close();

    // ifstream inFile("outFile.dat");

    // if (!inFile.is_open()) {
    //     cerr << "Error opening the file!"; 
    //     return 1;
    // }

    // AirportBST newBST = aBST.Load(inFile);
    // int height = newBST.GetHeight();
    // double avgDepth = newBST.AvgDepth();

    // cout << "--Reconstructed Tree--" << endl;
    // cout << "Height: " << height << "\t Average Depth: " << avgDepth << endl;
    // newBST.PrintLevelOrder(3);

    // cout << boolalpha;
    // cout << "--Original Tree--" << endl;
    // cout << "Valid Tree: " << aBST.Validate() << endl;
    // cout << "--Remove Leaf--" << endl;
    // aBST.Remove("DJJ"); 
    // cout << "Valid Tree: " << aBST.Validate() << endl;
    // cout << "--Remove Right Only--" << endl;
    // aBST.Remove("AAA");
    // cout << "Valid Tree: " << aBST.Validate() << endl;
    // cout << "--Remove Left Only--" << endl;
    // aBST.Remove("BOS");
    // cout << "Valid Tree: " << aBST.Validate() << endl;
    // cout << "--Remove Middle Node--" << endl;
    // aBST.Remove("EGS");
    // cout << "Valid Tree: " << aBST.Validate() << endl;
    // cout << "--Remove Root--" << endl;
    // aBST.Remove("GKA");
    // cout << "Valid Tree: " << aBST.Validate() << endl;

    // Airport* newAiport = new Airport("Q Airport", "Q City", "United States of America", "QQQ", "BAQQ", 10.1, 11.1);
    // aBST.Insert(newAiport);
    // aBST.Find("QQQ");
    // cout << "--Remove QQQ--" << endl;
    // aBST.Remove("QQQ");
    // cout << "Valid Tree: " << aBST.Validate() << endl;
    // aBST.Find("QQQ");

    // Task 5
    // aBST.Range("BOS", "BWI");

    // Task 6
    ShapeExperiement(airportFile);

    // aBST.Free();
    // newBST.Free();
    return 0;
}