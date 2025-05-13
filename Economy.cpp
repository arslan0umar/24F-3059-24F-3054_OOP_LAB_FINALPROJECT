#include "Stronghold.h"
#include <iostream>
#include <string>
using namespace std;

Economy::Economy() : taxRate(10) {}

void Economy::setTaxRate(int newRate) {
    try {
        if (newRate < 0 || newRate > 50) {
            throw GameException("Tax rate must be between 0 and 50%!");
        }
        taxRate = newRate;
        cout << "Tax rate set to " << taxRate << "%.\n";
    }
    catch (const GameException& e) {
        cout << "Error: " << e.message << "\n";
    }
}

void Economy::manage(ResourceManager& rm, Peasant& peasant, Merchant& merchant, Noble& noble, int playerId) {
    try {
        int choice;
        cout << "\n===== Economy Menu =====\n";
        cout << "1. Adjust Tax Rate\n";
        cout << "2. Collect Taxes\n";
        cout << "3. View Economy Status\n";
        cout << "4. Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            cout << "Enter new tax rate (0-50%): ";
            int newRate;
            cin >> newRate;
            setTaxRate(newRate);
            // Adjust social class satisfaction based on tax rate
            int satisfactionChange = (taxRate > 20) ? -5 : (taxRate < 10) ? 5 : 0;
            peasant.updateSatisfaction(satisfactionChange);
            merchant.updateSatisfaction(satisfactionChange);
            noble.updateSatisfaction(satisfactionChange);
            if (satisfactionChange != 0) {
                cout << "Social classes' satisfaction changed by " << satisfactionChange << " due to tax rate adjustment.\n";
            }
            break;
        }
        case 2: {
            int revenue = taxRate * 10; // Simplified: 10 gold per percentage point
            rm.gather("Gold", revenue, playerId); // Added playerId
            cout << "Collected " << revenue << " gold in taxes.\n";
            // Higher taxes reduce satisfaction
            if (taxRate > 30) {
                peasant.updateSatisfaction(-10);
                merchant.updateSatisfaction(-5);
                cout << "High taxes have reduced peasant and merchant satisfaction.\n";
            }
            break;
        }
        case 3:
            display();
            break;
        case 4:
            cout << "Returning to main menu.\n";
            break;
        default:
            throw GameException("Invalid choice!");
        }
    }
    catch (const GameException& e) {
        cout << "Error: " << e.message << "\n";
    }
}

void Economy::display() const {
    cout << "Economy Status:\n";
    cout << "  Tax Rate: " << taxRate << "%\n";
    cout << "  Economic Stability: ";
    if (taxRate > 30) {
        cout << "Unstable due to high taxes.\n";
    }
    else if (taxRate > 15) {
        cout << "Moderate, but citizens are grumbling.\n";
    }
    else {
        cout << "Stable, citizens are content.\n";
    }
}