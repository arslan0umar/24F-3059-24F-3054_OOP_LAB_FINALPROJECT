#include "Stronghold.h"
#include <iostream>
using namespace std;

void Peasant::updateSatisfaction(int change) {
    try {
        satisfaction += change;
        if (satisfaction > 100) satisfaction = 100;
        if (satisfaction < 0) satisfaction = 0;
    }
    catch (const GameException& e) {
        cout << "Error: " << e.message << "\n";
    }
}

void Peasant::displayStatus() const {
    cout << "Peasant Status:\n";
    cout << "  Satisfaction: " << satisfaction << "%\n";
    cout << "  ";
    if (satisfaction > 80) cout << "Peasants are joyful and productive.";
    else if (satisfaction > 60) cout << "Peasants are content.";
    else if (satisfaction > 40) cout << "Peasants are discontent and grumbling.";
    else if (satisfaction > 20) cout << "Peasants are angry and rebellious.";
    else cout << "Peasants are on the verge of revolt!";
    cout << "\n";
}

int Peasant::checkEmigration(Population& pop) {
    try {
        if (satisfaction < 30) {
            int emigrants = pop.getTotal() / 10; // 10% may leave
            pop.modify(-emigrants);
            cout << emigrants << " peasants have emigrated due to low satisfaction.\n";
            return emigrants;
        }
        return 0;
    }
    catch (const GameException& e) {
        cout << "Error: " << e.message << "\n";
        return 0;
    }
}