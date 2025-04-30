#include "Stronghold.h"
#include <iostream>
using namespace std;

void Merchant::updateSatisfaction(int change) {
    satisfaction += change * 2; 
    if (satisfaction < 0) satisfaction = 0;
    if (satisfaction > 100) satisfaction = 100;
}

void Merchant::displayStatus() const {
    cout << "Merchant Status:\n";
    cout << "  Satisfaction: " << satisfaction << "%\n";

    if (satisfaction < 20) {
        cout << "  Warning: Merchants are leaving the kingdom!\n";
    }
    else if (satisfaction < 40) {
        cout << "  Merchants are concerned about trade conditions.\n";
    }
    else if (satisfaction < 60) {
        cout << "  Merchants are conducting business as usual.\n";
    }
    else if (satisfaction < 80) {
        cout << "  Merchants are prospering under your rule.\n";
    }
    else {
        cout << "  The merchant class is thriving and expanding rapidly.\n";
    }
}