#include "Stronghold.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void Leader::menu(Population& pop, Army& army) {
    srand(time(0));

    cout << "\n===== Leadership Options =====\n";
    cout << "Current Leader: " << name << " (Popularity: " << popularity << "%)\n";
    cout << "1. Hold Elections\n";
    cout << "2. Change Policy\n";
    cout << "3. Attempt Coup\n";
    cout << "4. Inspire Population\n";
    cout << "5. Back to Main Menu\n";
    cout << "Enter choice: ";

    int choice;
    cin >> choice;

    switch (choice) {
    case 1: {
        cout << "Elections are being held...\n";
        int oldPopularity = popularity;

        // Election results depend on current popularity
        int electionResult = rand() % 100;

        if (electionResult > popularity) {
            string newNames[] = { "Alexander", "Isabella", "Marcus", "Victoria", "William" };
            string lastName[] = { "the Great", "the Wise", "the Bold", "the Just", "the Merciful" };

            string oldName = name;
            name = newNames[rand() % 5] + " " + lastName[rand() % 5];
            popularity = 50 + (rand() % 30); // New leader starts with good popularity

            cout << oldName << " has been voted out!\n";
            cout << "The new leader is " << name << " with initial popularity of " << popularity << "%\n";

            // New leader affects army morale
            army.morale += 10;
            if (army.morale > 100) army.morale = 100;
        }
        else {
            popularity += 10; // Re-election boosts popularity
            if (popularity > 100) popularity = 100;

            cout << name << " has been re-elected!\n";
            cout << "Popularity increased to " << popularity << "%\n";

            // Re-election affects army morale positively
            army.morale += 5;
            if (army.morale > 100) army.morale = 100;
        }
        break;
    }
    case 2: {
        cout << "Choose policy change:\n";
        cout << "1. Military Focus\n";
        cout << "2. Economic Focus\n";
        cout << "3. Population Focus\n";

        int policyChoice;
        cin >> policyChoice;

        switch (policyChoice) {
        case 1:
            cout << name << " has shifted focus to military matters!\n";
            army.morale += 20;
            if (army.morale > 100) army.morale = 100;

            popularity -= 5; // Military focus might be unpopular
            if (popularity < 0) popularity = 0;

            cout << "Army morale increased to " << army.morale << "%\n";
            cout << "Leader popularity changed to " << popularity << "%\n";
            break;

        case 2:
            cout << name << " has shifted focus to economic growth!\n";
            popularity += 10; // Economic focus is generally popular
            if (popularity > 100) popularity = 100;

            cout << "Leader popularity increased to " << popularity << "%\n";
            break;

        case 3:
            cout << name << " has shifted focus to population welfare!\n";
            pop.modify(pop.getTotal() / 10); // Population increases

            popularity += 15; // Population focus is very popular
            if (popularity > 100) popularity = 100;

            cout << "Population has grown thanks to welfare policies.\n";
            cout << "Leader popularity increased to " << popularity << "%\n";
            break;

        default:
            cout << "Invalid policy choice.\n";
        }
        break;
    }
    case 3: {
        cout << "Attempting a coup against " << name << "...\n";

        // Coup success depends on leader popularity and army morale
        int coupChance = 100 - popularity + (50 - army.morale / 2);
        int coupResult = rand() % 100;

        if (coupResult < coupChance) {
            string oldName = name;
            name = "General " + string(1, 'A' + (rand() % 26)) + ". " + string(1, 'A' + (rand() % 26)) + ".";
            popularity = 40 + (rand() % 20); // Military leaders start with moderate popularity

            cout << "The coup was successful! " << oldName << " has been overthrown!\n";
            cout << "The new leader is " << name << " with initial popularity of " << popularity << "%\n";

            // Coup affects army and population
            army.morale += 15;
            if (army.morale > 100) army.morale = 100;
            pop.modify(-pop.getTotal() / 20); // Some population lost in the coup
        }
        else {
            cout << "The coup attempt failed! Guards have arrested the rebels.\n";

            popularity -= 15; // Failed coup hurts popularity
            if (popularity < 0) popularity = 0;

            army.morale -= 20; // Failed coup hurts army morale
            if (army.morale < 0) army.morale = 0;

            cout << "Leader popularity decreased to " << popularity << "%\n";
            cout << "Army morale decreased to " << army.morale << "%\n";
        }
        break;
    }
    case 4: {
        cout << name << " gives an inspiring speech to the population!\n";

        // Speech effectiveness depends on leader popularity
        int speechEffect = 5 + (popularity / 10);

        popularity += 5;
        if (popularity > 100) popularity = 100;

        army.morale += speechEffect / 2;
        if (army.morale > 100) army.morale = 100;

        cout << "The speech was well received!\n";
        cout << "Leader popularity increased to " << popularity << "%\n";
        cout << "Army morale increased to " << army.morale << "%\n";
        break;
    }
    case 5:
        cout << "Returning to main menu.\n";
        break;

    default:
        cout << "Invalid option.\n";
    }
}

void Leader::display() const {
    cout << "Leadership Status:\n";
    cout << "  Current ruler: " << name << endl;
    cout << "  Popularity: " << popularity << "%" << endl;

    cout << "  Leadership strength: ";
    if (popularity > 80) {
        cout << "Beloved";
    }
    else if (popularity > 60) {
        cout << "Respected";
    }
    else if (popularity > 40) {
        cout << "Tolerated";
    }
    else if (popularity > 20) {
        cout << "Disliked";
    }
    else {
        cout << "Hated - rebellion risk!";
    }
    cout << endl;
}