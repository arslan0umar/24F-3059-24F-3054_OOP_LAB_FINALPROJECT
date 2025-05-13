#include "Stronghold.h"
#include <iostream>
using namespace std;

Army::Army() : soldiers(100), morale(50) {}

void Army::setSoldiers(int newSoldiers) {
    try {
        if (newSoldiers < 0) {
            throw GameException("Soldier count cannot be negative!");
        }
        soldiers = newSoldiers;
    }
    catch (const GameException& e) {
        cout << "Error: " << e.message << "\n";
    }
}

void Army::setMorale(int newMorale) {
    try {
        morale = newMorale;
        if (morale > 100) morale = 100;
        if (morale < 0) morale = 0;
    }
    catch (const GameException& e) {
        cout << "Error: " << e.message << "\n";
    }
}

void Army::train(ResourceManager& rm) {
    try {
        if (!rm.hasResource("Food", 20) || !rm.hasResource("Gold", 10)) {
            throw GameException("Not enough resources to train army!");
        }
        rm.consume("Food", 20, 0); // Player ID 0 for non-player-specific actions
        rm.consume("Gold", 10, 0);
        soldiers += 10;
        morale += 5;
        if (morale > 100) morale = 100;
        cout << "Trained 10 soldiers. New total: " << soldiers << ", Morale: " << morale << "%\n";
    }
    catch (const GameException& e) {
        cout << "Error: " << e.message << "\n";
    }
}

void Army::pay(ResourceManager& rm) {
    try {
        if (!rm.hasResource("Gold", 5)) {
            throw GameException("Not enough gold to pay army!");
        }
        rm.consume("Gold", 5, 0);
        morale += 10;
        if (morale > 100) morale = 100;
        cout << "Paid army. Morale increased to " << morale << "%\n";
    }
    catch (const GameException& e) {
        cout << "Error: " << e.message << "\n";
    }
}

void Army::display() const {
    cout << "Army Status:\n";
    cout << "  Soldiers: " << soldiers << "\n";
    cout << "  Morale: " << morale << "%\n";
    cout << "  Strength: " << (soldiers * morale / 100) << "\n";
}