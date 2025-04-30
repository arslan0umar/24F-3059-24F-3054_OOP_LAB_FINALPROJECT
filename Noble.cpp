#include "Stronghold.h"
#include <iostream>
using namespace std;

void Noble::updateSatisfaction(int change) {
    satisfaction += change / 2;
    if (satisfaction < 0) satisfaction = 0;
    if (satisfaction > 100) satisfaction = 100;
}

int Noble::checkEmigration(Population& pop) {
    int emigrants = 0;

    if (satisfaction < 10) {
        // Mass exodus when satisfaction is critically low
        emigrants = pop.getTotal() / 15; // ~6.7% leave
        cout << "CRISIS: Noble families are fleeing to neighboring kingdoms!\n";
    }
    else if (satisfaction < 25) {
        // Significant emigration
        emigrants = pop.getTotal() / 25; // 4% leave
        cout << "WARNING: Some noble houses have packed up and left your realm!\n";
    }
    else if (satisfaction < 40) {
        // Small emigration
        emigrants = pop.getTotal() / 50; // 2% leave
        cout << "A few noble families have chosen to relocate to other lands.\n";
    }

    // Ensure at least 1 person leaves if calculated to leave
    if (emigrants > 0 && emigrants < 1) emigrants = 1;

    if (emigrants > 0) {
        pop.modify(-emigrants);
    }

    return emigrants;
}

void Noble::displayStatus() const {
    cout << "Noble Status:\n";
    cout << "  Satisfaction: " << satisfaction << "%\n";

    if (satisfaction < 20) {
        cout << "  Warning: Nobles are plotting against you!\n";
    }
    else if (satisfaction < 40) {
        cout << "  Nobles are discontent with your leadership.\n";
    }
    else if (satisfaction < 60) {
        cout << "  Nobles tolerate your rule with reservation.\n";
    }
    else if (satisfaction < 80) {
        cout << "  Nobles support your decisions.\n";
    }
    else {
        cout << "  The noble houses are firmly allied with your throne.\n";
    }
}