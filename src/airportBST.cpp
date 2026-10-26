#include <string>
#include <iostream>

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

double AirportBST::AvgHeight()
{
    int totalNodes = 0;
    int sumDepth = SumDepth(root, 0, totalNodes);
    return sumDepth / totalNodes;
}

Airport* AirportBST::find(string code)
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

void AirportBST::findMin()
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

void AirportBST::findMax()
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
