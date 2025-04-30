#include "Stronghold.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
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

void Population::naturalChange() {
    // Random fluctuation in population based on natural causes
    int randFactor = rand() % 100;
    int change = 0;

    if (randFactor < 30) {
        // 30% chance of population decrease due to natural causes
        change = -(rand() % 5 + 1); // Decrease by 1-5 people
        cout << "Some citizens have passed away due to natural causes or have migrated from the kingdom.\n";
    }
    else if (randFactor < 70) {
        // 40% chance of population increase due to births
        change = rand() % 3 + 1; // Increase by 1-3 people
        cout << "New births and incoming settlers have slightly increased your population.\n";
    }
    // 30% chance of no change

    if (change != 0) {
        modify(change);
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