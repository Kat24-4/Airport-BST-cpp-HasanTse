#pragma once 

#include <string>

using namespace std;

class Airport {
    public:
        string name;
        string city; 
        string country;
        string iataCode;
        string icaoCode;
        double latitude;
        double longitude;
        Airport* left;
        Airport* right;

        Airport(string n, string cty, string ctry, string iata, string icao, double lat, double lon) {
            name = n;
            city = cty; 
            country = ctry;
            iataCode = iata;
            icaoCode = icao;
            latitude = lat;
            longitude = lon;
            left = nullptr;
            right = nullptr;
        }
};