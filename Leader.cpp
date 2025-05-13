#include "Stronghold.h"
#include <iostream>
#include <string>
#include <ctime>
using namespace std;

Leader::Leader() : name("Unknown"), popularity(50) {
    srand(time(0));
}

void Leader::setName(const string& newName) {
    try {
        if (newName.empty()) {
            throw GameException("Name cannot be empty!");
        }
        name = newName;
    }
    catch (const GameException& e) {
        cout << "Error: " << e.message << "\n";
    }
}

void Leader::setPopularity(int newPopularity) {
    try {
        if (newPopularity < 0 || newPopularity > 100) {
            throw GameException("Popularity must be between 0 and 100!");
        }
        popularity = newPopularity;
    }
    catch (const GameException& e) {
        cout << "Error: " << e.message << "\n";
    }
}

void Leader::menu(Population& pop, Army& army) {
    try {
        int choice;
        cout << "\n===== Leadership Menu =====\n";
        cout << "1. Address the Population\n";
        cout << "2. Inspect Army\n";
        cout << "3. Change Name\n";
        cout << "4. Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            cout << "Addressing the population...\n";
            int effect = rand() % 10 - 5; // Random effect between -5 and +4
            setPopularity(popularity + effect);
            pop.modify(effect * 10); // Population changes based on speech
            cout << "Popularity changed by " << effect << ". New popularity: " << popularity << "%\n";
            break;
        }
        case 2: {
            cout << "Inspecting the army...\n";
            army.display();
            int newMorale = army.getMorale() + (rand() % 10); // Random morale boost
            if (newMorale > 100) newMorale = 100;
            army.setMorale(newMorale);
            cout << "Army morale updated to " << newMorale << "%\n";
            break;
        }
        case 3: {
            cout << "Enter new leader name: ";
            cin.ignore();
            string newName;
            getline(cin, newName);
            setName(newName);
            cout << "Leader name changed to " << name << "\n";
            break;
        }
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

void Leader::display() const {
    cout << "Current ruler: " << name << "\n";
    cout << "Popularity: " << popularity << "%\n";
    cout << "Leadership strength: ";
    if (popularity > 80) cout << "Adored";
    else if (popularity > 60) cout << "Respected";
    else if (popularity > 40) cout << "Tolerated";
    else if (popularity > 20) cout << "Disliked";
    else cout << "Despised";
    cout << "\n";
}