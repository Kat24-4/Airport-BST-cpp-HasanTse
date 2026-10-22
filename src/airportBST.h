#pragma once

#include <string>
#include "airport.h"

using namespace std;

class AirportBST {
    private:
        Airport* root;

        int SumDepth(Airport* node, int d, int& totalNodes);
        int Height(Airport* node);

    public:
        AirportBST();
        string Insert(Airport* newAirport);
        int GetHeight();
        double AvgHeight();
};