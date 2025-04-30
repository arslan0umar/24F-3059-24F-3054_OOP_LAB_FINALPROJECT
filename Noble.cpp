#include "Stronghold.h"
#include <iostream>
using namespace std;

void Noble::updateSatisfaction(int change) {
    satisfaction += change / 2; 
    if (satisfaction < 0) satisfaction = 0;
    if (satisfaction > 100) satisfaction = 100;
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