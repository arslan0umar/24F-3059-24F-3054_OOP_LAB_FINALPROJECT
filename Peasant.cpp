#include "Stronghold.h"
#include <iostream>
using namespace std;

void Peasant::updateSatisfaction(int change) {
    satisfaction += change;
    if (satisfaction < 0) satisfaction = 0;
    if (satisfaction > 100) satisfaction = 100;
}

void Peasant::displayStatus() const {
    cout << "Peasant Status:\n";
    cout << "  Satisfaction: " << satisfaction << "%\n";

    if (satisfaction < 20) {
        cout << "  Warning: Peasants are close to rebellion!\n";
    }
    else if (satisfaction < 40) {
        cout << "  Peasants are discontent and grumbling.\n";
    }
    else if (satisfaction < 60) {
        cout << "  Peasants are acceptably content.\n";
    }
    else if (satisfaction < 80) {
        cout << "  Peasants are satisfied with their conditions.\n";
    }
    else {
        cout << "  Peasants are extremely happy with your rule.\n";
    }
}