#pragma once

#include <string>
#include <fstream>
#include "airport.h"

using namespace std;

class AirportBST {
    private:
        Airport* root;

        int SumDepth(Airport* node, int d, int& totalNodes);
        int Height(Airport* node);
        Airport* RecursiveRemove(Airport* node, string code);
        void RecursiveList(Airport* node);
        void RecursiveSave(Airport* node, ofstream &file);
        bool RecursiveValidate(Airport* node, string minKey, string maxKey);
        void RecursiveRange(Airport* node, string from, string to, int& nodesVisited);
        Airport* RecursiveBuildBalanced(vector<Airport*> airports, int low, int high);

    public:
        AirportBST();
        string Insert(Airport* newAirport);
        int GetHeight();
        double AvgDepth();
        Airport* Find(string code);
        void FindMin();
        void FindMax();
        void Remove(string code);
        void AirportBST::PrintLevelOrder(int levels);
        void List();
        void Save(ofstream &file);
        AirportBST Load(ifstream &file);
        bool Validate();
        int Range(string from, string to);
        void BuildBalanced(vector<Airport*> airports, int n);
};