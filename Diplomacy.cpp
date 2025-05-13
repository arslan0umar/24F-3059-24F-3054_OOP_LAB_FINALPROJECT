#include "Stronghold.h"
#include <iostream>
#include <fstream>
using namespace std;

Diplomacy::Diplomacy() : treatyCount(0) {}

void Diplomacy::formAlliance(int player1, int player2) {
    try {
        if (player1 == player2) {
            throw GameException("Cannot form alliance with self!");
        }
        for (int i = 0; i < treatyCount; i++) {
            if (treaties[i].player1 == player1 && treaties[i].player2 == player2 && treaties[i].active) {
                throw GameException("Alliance already exists!");
            }
        }
        if (treatyCount >= 20) {
            throw GameException("Treaty log is full!");
        }
        treaties[treatyCount].player1 = player1;
        treaties[treatyCount].player2 = player2;
        treaties[treatyCount].active = true;
        treatyCount++;
        cout << "Alliance formed between Player " << player1 << " and Player " << player2 << ".\n";
        saveTreaties();
    }
    catch (const GameException& e) {
        cout << "Error: " << e.message << "\n";
    }
}

void Diplomacy::breakAlliance(int player1, int player2) {
    try {
        bool found = false;
        for (int i = 0; i < treatyCount; i++) {
            if (treaties[i].player1 == player1 && treaties[i].player2 == player2 && treaties[i].active) {
                treaties[i].active = false;
                found = true;
                cout << "Alliance broken between Player " << player1 << " and Player " << player2 << ".\n";
                saveTreaties();
                break;
            }
        }
        if (!found) {
            throw GameException("No active alliance found between Player " + to_string(player1) + " and Player " + to_string(player2));
        }
    }
    catch (const GameException& e) {
        cout << "Error: " << e.message << "\n";
    }
}

bool Diplomacy::hasAlliance(int player1, int player2) const {
    for (int i = 0; i < treatyCount; i++) {
        if (treaties[i].player1 == player1 && treaties[i].player2 == player2 && treaties[i].active) {
            return true;
        }
    }
    return false;
}

void Diplomacy::displayTreaties() const {
    cout << "Active Treaties:\n";
    bool found = false;
    for (int i = 0; i < treatyCount; i++) {
        if (treaties[i].active) {
            cout << "Player " << treaties[i].player1 << " and Player " << treaties[i].player2 << "\n";
            found = true;
        }
    }
    if (!found) {
        cout << "No active treaties.\n";
    }
}

void Diplomacy::saveTreaties() const {
    ofstream file("treaties.txt");
    if (file.is_open()) {
        for (int i = 0; i < treatyCount; i++) {
            file << treaties[i].player1 << " " << treaties[i].player2 << " " << (treaties[i].active ? 1 : 0) << "\n";
        }
        file.close();
    }
    else {
        cout << "Error: Unable to save treaties.\n";
    }
}

void Diplomacy::loadTreaties() {
    ifstream file("treaties.txt");
    treatyCount = 0;
    if (file.is_open()) {
        while (file >> treaties[treatyCount].player1 >> treaties[treatyCount].player2 >> treaties[treatyCount].active && treatyCount < 20) {
            treatyCount++;
        }
        file.close();
    }
    else {
        cout << "Error: Unable to load treaties.\n";
    }
}