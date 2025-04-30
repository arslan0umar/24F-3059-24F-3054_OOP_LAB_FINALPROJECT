#include "Stronghold.h"
#include <iostream>
using namespace std;

Population::Population() : count(100) {}

void Population::modify(int amt) {
    count += amt;
    if (count < 0) {
        count = 0;
        cout << "Warning: Population has been completely wiped out!\n";
    }
    else {
        cout << "Population changed by " << amt << ". New population: " << count << ".\n";
    }
}

void Population::display() const {
    cout << "Population Status:\n";
    cout << "  Total citizens: " << count << endl;

    cout << "  Population state: ";
    if (count > 500) {
        cout << "Thriving metropolis";
    }
    else if (count > 300) {
        cout << "Growing city";
    }
    else if (count > 200) {
        cout << "Modest town";
    }
    else if (count > 100) {
        cout << "Small settlement";
    }
    else if (count > 50) {
        cout << "Struggling village";
    }
    else if (count > 0) {
        cout << "Nearly abandoned";
    }
    else {
        cout << "Ghost town";
    }
    cout << endl;
}