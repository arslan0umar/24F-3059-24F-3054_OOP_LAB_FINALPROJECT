#include "Stronghold.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

Market::Market() : tradeCount(0) {}

void Market::trade(ResourceManager& rm1, ResourceManager& rm2, int resourceNum1, int resourceNum2, int amount, int player1, int player2) {
    try {
        if (player1 == player2) {
            throw GameException("Cannot trade with self!");
        }
        if (amount <= 0) {
            throw GameException("Trade amount must be positive!");
        }
        if (resourceNum1 < 1 || resourceNum1 > rm1.getResourceCount() || resourceNum2 < 1 || resourceNum2 > rm2.getResourceCount()) {
            throw GameException("Invalid resource number!");
        }
        string resource1 = rm1.getResourceName(resourceNum1 - 1);
        string resource2 = rm2.getResourceName(resourceNum2 - 1);
        if (!rm1.hasResource(resource1, amount)) {
            throw GameException("Player " + to_string(player1) + " does not have enough " + resource1 + "!");
        }
        // 1:1 trade ratio
        rm1.consume(resource1, amount, player1);
        rm2.gather(resource2, amount, player2);
        rm2.consume(resource2, amount, player2);
        rm1.gather(resource1, amount, player1);
        cout << "Player " << player1 << " traded " << amount << " units of " << resource1
            << " for " << amount << " units of " << resource2 << " with Player " << player2 << ".\n";
        if (tradeCount < 50) {
            trades[tradeCount].player1 = player1;
            trades[tradeCount].player2 = player2;
            trades[tradeCount].resource = resource1 + " for " + resource2;
            trades[tradeCount].amount = amount;
            trades[tradeCount].isSmuggling = false;
            tradeCount++;
            saveMarket();
        }
    }
    catch (const GameException& e) {
        cout << "Error: " << e.message << "\n";
    }
}

void Market::smuggle(ResourceManager& rm1, ResourceManager& rm2, const string& resource, int amount, int player1, int player2) {
    try {
        if (player1 == player2) {
            throw GameException("Cannot smuggle with self!");
        }
        if (amount <= 0) {
            throw GameException("Smuggle amount must be positive!");
        }
        if (!rm1.hasResource(resource, amount)) {
            throw GameException("Player " + to_string(player1) + " does not have enough " + resource + "!");
        }
        rm1.consume(resource, amount, player1);
        rm2.gather(resource, amount * 2, player2); // Smuggling yields double
        cout << "Player " << player1 << " smuggled " << amount << " units of " << resource
            << " to Player " << player2 << ", who received " << (amount * 2) << " units.\n";
        if (tradeCount < 50) {
            trades[tradeCount].player1 = player1;
            trades[tradeCount].player2 = player2;
            trades[tradeCount].resource = resource;
            trades[tradeCount].amount = amount;
            trades[tradeCount].isSmuggling = true;
            tradeCount++;
            saveMarket();
        }
    }
    catch (const GameException& e) {
        cout << "Error: " << e.message << "\n";
    }
}

void Market::displayMarket() const {
    cout << "Market Transactions:\n";
    if (tradeCount == 0) {
        cout << "  No transactions recorded.\n";
    }
    else {
        for (int i = 0; i < tradeCount; i++) {
            cout << "  " << (trades[i].isSmuggling ? "Smuggling" : "Trade") << ": Player "
                << trades[i].player1 << " and Player " << trades[i].player2
                << ", Resource: " << trades[i].resource << ", Amount: " << trades[i].amount << "\n";
        }
    }
}

void Market::saveMarket() const {
    try {
        ofstream file("market.txt");
        if (!file.is_open()) {
            throw GameException("Unable to open market.txt for saving!");
        }
        for (int i = 0; i < tradeCount; i++) {
            file << trades[i].player1 << " " << trades[i].player2 << " "
                << trades[i].resource << " " << trades[i].amount << " "
                << (trades[i].isSmuggling ? 1 : 0) << "\n";
        }
        file.close();
    }
    catch (const GameException& e) {
        cout << "Error: " << e.message << "\n";
    }
}

void Market::loadMarket() {
    try {
        ifstream file("market.txt");
        if (!file.is_open()) {
            throw GameException("Unable to open market.txt for loading!");
        }
        tradeCount = 0;
        while (file >> trades[tradeCount].player1 >> trades[tradeCount].player2
            && getline(file, trades[tradeCount].resource) // Read until space
            && file >> trades[tradeCount].amount >> trades[tradeCount].isSmuggling
            && tradeCount < 50) {
            trades[tradeCount].resource = trades[tradeCount].resource.substr(1); // Remove leading space
            tradeCount++;
        }
        file.close();
    }
    catch (const GameException& e) {
        cout << "Error: " << e.message << "\n";
    }
}