#include <string>
#include <iostream>
#include <fstream>
#include <queue>
#include "airportBST.h"

using namespace std;

// Private Functions
int AirportBST::SumDepth(Airport* node, int d, int& totalNodes)
{
    if (node == nullptr) {
        return 0;
    }
    
    totalNodes++;
    return d + SumDepth(node->left, d+1, totalNodes) + SumDepth(node->right, d+1, totalNodes);
}

int AirportBST::Height(Airport* node)
{
    if (node == nullptr) {
        return -1;
    }

    int leftHeight = Height(node->left);
    int rightHeight = Height(node->right);

    if (leftHeight < rightHeight) {
        return 1 + rightHeight;
    } else {
        return 1 + leftHeight;
    }
}

Airport* AirportBST::RecursiveRemove(Airport* node, string code)
{
    if (node == nullptr){
        return;
    }
    if (code < node->iataCode){
        node->left = RecursiveRemove(node->left, code);
    } else if (code > node->iataCode){
        node->right = RecursiveRemove(node->right, code);   
    } else {
        if (node->left == nullptr) {
            return node->right;
        }
        if (node->right == nullptr) {
            return node->left;
        }
        Airport* s = node->right;
        while (s->left != nullptr){
            s = s->left;
        }
        node->name = s->name;
        node->city = s->city;
        node->country = s->country;
        node->iataCode = s->iataCode;
        node->icaoCode = s->icaoCode;
        node->latitude = s->latitude;
        node->longitude = s->longitude;
        node->right = RecursiveRemove(node->right, s->iataCode);
    }
    return node;
}

void AirportBST::RecursiveList(Airport* node) {
    if (node == nullptr) {
        return;
    }
    RecursiveList(node->left);
    cout << node->iataCode << ": " << node->name << ", " << node->city << ", "
        << node->country << ", " << node->icaoCode << " [" << node->latitude << 
        ", " << node->longitude << "]" << endl;
    RecursiveList(node->right);
}

void AirportBST::RecursiveSave(Airport* node, ofstream &file) {
    if (node == nullptr) {
        return;
    }

    file << node->iataCode << "\n";
    RecursiveSave(node->left, file);
    RecursiveSave(node->right, file);
}

bool AirportBST::RecursiveValidate(Airport* node, string minKey, string maxKey) {
    if (node == nullptr) {
        return true; 
    }
    if (minKey != "" && node->iataCode <= minKey) {
        return false;
    }
    if (maxKey != "" && node->iataCode >= maxKey) {
        return false;
    }
    bool leftValid = RecursiveValidate(node->left, minKey, node->iataCode);
    bool rightValid = RecursiveValidate(node->right, node->iataCode, maxKey);
    return leftValid && rightValid; 
}

void AirportBST::RecursiveRange(Airport* node, string from, string to, int& nodesVisited)
{
    if (node == nullptr) {
        return;
    }
    nodesVisited++;

    if (node->left->iataCode >= from) {
        RecursiveRange(node->left, from, to, nodesVisited);
    }
    cout << node->iataCode;

    if (node->right->iataCode <= to) {
        RecursiveRange(node->right, from, to, nodesVisited);
    }
}

Airport* AirportBST::RecursiveBuildBalanced(vector<Airport*> airports, int low, int high) {
    if (low > high) {
        return nullptr;
    }

    int mid = (low + high) / 2;
    Airport* currNode = airports[mid]; 
    Airport newNode = Airport(currNode->name, currNode->city, currNode->country, currNode->iataCode, currNode->icaoCode, currNode->latitude, currNode->longitude);
    newNode.left = RecursiveBuildBalanced(airports, low, mid - 1);
    newNode.right = RecursiveBuildBalanced(airports, mid + 1, high);
    return &newNode; 
}

// Public Functions
AirportBST::AirportBST()
{
    root = nullptr;
}

string AirportBST::Insert(Airport* newAirport)
{
    if (root == nullptr) {
        root = newAirport;
        return "Added";
    }

    Airport* curr = root;
    while (true) {
        if (newAirport->iataCode < curr->iataCode) {
            if (curr->left == nullptr) {
                curr->left = newAirport; 
                return "Added";
            }
            curr = curr->left;
        } else if (newAirport->iataCode > curr->iataCode) {
            if (curr->right == nullptr) {
                curr->right = newAirport;
                return "Added";
            }
            curr = curr->right;
        } else {
            return "Duplicate";
        }
    }
}

int AirportBST::GetHeight()
{
    return Height(root);
}

double AirportBST::AvgDepth()
{
    int totalNodes = 0;
    int sumDepth = SumDepth(root, 0, totalNodes);
    return sumDepth / totalNodes;
}

Airport* AirportBST::Find(string code)
{
    Airport* curr = root;
    int comparisons = 0;
    cout << "Path: ";

    while (curr != nullptr)
    {
        comparisons++;
        cout << curr->iataCode;

        if (code == curr->iataCode)
        {
            cout << " (Comparisons: " << comparisons << ")" << endl;
            cout << curr->iataCode << ", " << curr->name << ", " << curr->city << ", "
                 << curr->country << ", " << curr->icaoCode << ", "
                 << curr->latitude << ", " << curr->longitude << endl;
            return curr;
        }
        else if (code < curr->iataCode)
        {
            curr = curr->left;
        }
        else
        {
            curr = curr->right;
        }
        cout << " -> ";
    }

    cout << "(NULL) not found" << endl;
}

void AirportBST::FindMin()
{
    if (root == nullptr) {
        cout << "Tree is empty" << endl;
        return;
    }

    Airport* curr = root;
    while (curr->left != nullptr)
    {
        curr = curr->left;
    }
    cout << "Minimum: " << curr->iataCode << endl;
}

void AirportBST::FindMax()
{
    if (root == nullptr) {
        cout << "Tree is empty" << endl;
        return;
    }

    Airport* curr = root;
    while (curr->right != nullptr)
    {
        curr = curr->right;
    }
    cout << "Maximum: " << curr->iataCode << endl;
}

void AirportBST::Remove(string code)
{
    root = RecursiveRemove(root, code);
}

void AirportBST::PrintLevelOrder(int levels)
{
    if (root == nullptr){
        cout << "Empty Tree" << endl;
        return;
    }

    queue<Airport*> q;
    q.push(root);
    int currLevel = 1;

    while (!q.empty() && currLevel <= levels) {
        int levelSize = q.size();

        for (int i = 0; i < levelSize; i++) {
            Airport* currNode = q.front();
            q.pop();
            cout << currNode->iataCode << " ";;

            if (currNode->left != nullptr) {
                q.push(currNode->left);
            }
            if (currNode->right != nullptr) {
                q.push(currNode->right);
            }
        }
        cout << endl;
        currLevel++;
    }
}


void AirportBST::List() {
    RecursiveList(root);
}

void AirportBST::Save(ofstream &file) {
    if (!file.is_open()) {
        cout << "Invalid File" << endl;
        return; 
    }
    RecursiveSave(root, file);
}

AirportBST AirportBST::Load(ifstream &file) {
    if (!file.is_open()) {
        cout << "Invalid File" << endl;
        return; 
    }

    string line; 
    AirportBST newBST = AirportBST();

    while (getline(file, line)) {
        Airport* currNode = Find(line);
        Airport newNode = Airport(currNode->name, currNode->city, currNode->country, currNode->iataCode, currNode->icaoCode, currNode->latitude, currNode->longitude);
        newBST.Insert(&newNode);
    }

    return newBST;
}

bool AirportBST::Validate() {
    return RecursiveValidate(root, "", "");
}

int AirportBST::Range(string from, string to)
{
    int nodesVisited = 0;
    RecursiveRange(root, from, to, nodesVisited);
    return nodesVisited;
}

void AirportBST::BuildBalanced(vector<Airport*> airports, int n) {
    root = RecursiveBuildBalanced(airports, 0, n - 1);
}