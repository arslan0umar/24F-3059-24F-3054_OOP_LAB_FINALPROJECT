#include "Stronghold.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int MAX_POPULATION = 1000;

Population::Population() : count(100) {
    srand(time(0));
}

void Population::setTotal(int newCount) {
    try {
        if (newCount < 0) {
            throw GameException("Population cannot be negative!");
        }
        if (newCount > MAX_POPULATION) {
            throw GameException("Population exceeds maximum limit of " + to_string(MAX_POPULATION));
        }
        count = newCount;
    }
    catch (const GameException& e) {
        cout << "Error: " << e.message << "\n";
    }
}

void Population::modify(int amt) {
    try {
        int newCount = count + amt;
        if (newCount < 0) {
            throw GameException("Population cannot be negative!");
        }
        if (newCount > MAX_POPULATION) {
            throw GameException("Population exceeds maximum limit of " + to_string(MAX_POPULATION));
        }
        count = newCount;
        cout << "Population modified by " << amt << ". New total: " << count << "\n";
    }
    catch (const GameException& e) {
        cout << "Error: " << e.message << "\n";
    }
}

void Population::naturalChange() {
    try {
        // Always add 3 for consistent growth
        int baseGrowth = 3;
        // Random change: -20 to +20
        int randomChange = (rand() % 41) - 20; // Generates -20 to +20
        int netChange = baseGrowth + randomChange;
        int newCount = count + netChange;
        if (newCount < 0) {
            throw GameException("Population cannot be negative!");
        }
        if (newCount > MAX_POPULATION) {
            throw GameException("Population exceeds maximum limit of " + to_string(MAX_POPULATION));
        }
        count = newCount;
        cout << "Population changed by " << netChange << " (Base: +3, Random: " << randomChange << "). New total: " << count << "\n";
    }
    catch (const GameException& e) {
        cout << "Error: " << e.message << "\n";
    }
}

void Population::display() const {
    cout << "Total citizens: " << count << "\n";
    cout << "Population state: ";
    if (count > 500) cout << "Thriving city";
    else if (count > 200) cout << "Growing town";
    else if (count > 50) cout << "Small settlement";
    else cout << "Struggling hamlet";
    cout << "\n";
}