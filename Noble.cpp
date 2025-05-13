#include "Stronghold.h"
#include <iostream>
using namespace std;

void Noble::updateSatisfaction(int change) {
    try {
        satisfaction += change;
        if (satisfaction > 100) satisfaction = 100;
        if (satisfaction < 0) satisfaction = 0;
    }
    catch (const GameException& e) {
        cout << "Error: " << e.message << "\n";
    }
}

void Noble::displayStatus() const {
    cout << "Noble Status:\n";
    cout << "  Satisfaction: " << satisfaction << "%\n";
    cout << "  ";
    if (satisfaction > 80) cout << "Nobles are loyal and supportive.";
    else if (satisfaction > 60) cout << "Nobles are cooperative.";
    else if (satisfaction > 40) cout << "Nobles tolerate your rule with reservation.";
    else if (satisfaction > 20) cout << "Nobles are plotting against you.";
    else cout << "Nobles are openly rebellious!";
    cout << "\n";
}

int Noble::checkEmigration(Population& pop) {
    try {
        if (satisfaction < 20) {
            int emigrants = pop.getTotal() / 50; // 2% may leave
            pop.modify(-emigrants);
            cout << emigrants << " nobles have emigrated due to low satisfaction.\n";
            return emigrants;
        }
        return 0;
    }
    catch (const GameException& e) {
        cout << "Error: " << e.message << "\n";
        return 0;
    }
}