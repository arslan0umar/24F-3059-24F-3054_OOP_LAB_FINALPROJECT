#include "Stronghold.h"
#include <iostream>
using namespace std;

void Merchant::updateSatisfaction(int change) {
    try {
        satisfaction += change;
        if (satisfaction > 100) satisfaction = 100;
        if (satisfaction < 0) satisfaction = 0;
    }
    catch (const GameException& e) {
        cout << "Error: " << e.message << "\n";
    }
}

void Merchant::displayStatus() const {
    cout << "Merchant Status:\n";
    cout << "  Satisfaction: " << satisfaction << "%\n";
    cout << "  ";
    if (satisfaction > 80) cout << "Merchants are thriving and investing heavily.";
    else if (satisfaction > 60) cout << "Merchants are conducting business as usual.";
    else if (satisfaction > 40) cout << "Merchants are cautious and reducing trade.";
    else if (satisfaction > 20) cout << "Merchants are hoarding wealth.";
    else cout << "Merchants are fleeing the kingdom!";
    cout << "\n";
}

int Merchant::checkEmigration(Population& pop) {
    try {
        if (satisfaction < 40) {
            int emigrants = pop.getTotal() / 20; // 5% may leave
            pop.modify(-emigrants);
            cout << emigrants << " merchants have emigrated due to low satisfaction.\n";
            return emigrants;
        }
        return 0;
    }
    catch (const GameException& e) {
        cout << "Error: " << e.message << "\n";
        return 0;
    }
}