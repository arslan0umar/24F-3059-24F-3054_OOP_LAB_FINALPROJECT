#include "Stronghold.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

void Logger::logScore(const string& info) {
    try {
        ofstream file("score_log.txt", ios::app);
        if (!file.is_open()) {
            throw GameException("Unable to open score_log.txt!");
        }
        file << info << "\n";
        file.close();
    }
    catch (const GameException& e) {
        cout << "Error: " << e.message << "\n";
    }
}

void Logger::saveGame(const Population& pop, const Army& army,
    const Bank& bank, const Leader& leader,
    const ResourceManager& rm, const Economy& economy,
    const Peasant& peasant, const Merchant& merchant, const Noble& noble) {
    try {
        ofstream file("game_save.txt");
        if (!file.is_open()) {
            throw GameException("Unable to open game_save.txt for saving!");
        }
        file << pop.getTotal() << "\n";
        file << army.getSoldiers() << " " << army.getMorale() << "\n";
        file << bank.getLoan() << "\n";
        file << leader.getName() << " " << leader.getPopularity() << "\n";
        file << rm.getResourceCount() << "\n";
        for (int i = 0; i < rm.getResourceCount(); i++) {
            file << rm.getResourceName(i) << " " << rm.getResourceValue(i) << "\n";
        }
        file << economy.getTaxRate() << "\n";
        file << peasant.getSatisfaction() << "\n";
        file << merchant.getSatisfaction() << "\n";
        file << noble.getSatisfaction() << "\n";
        file.close();
        cout << "Game saved successfully.\n";
    }
    catch (const GameException& e) {
        cout << "Error: " << e.message << "\n";
    }
}

bool Logger::loadGame(Population& pop, Army& army, Bank& bank,
    Leader& leader, ResourceManager& rm, Economy& economy,
    Peasant& peasant, Merchant& merchant, Noble& noble) {
    try {
        ifstream file("game_save.txt");
        if (!file.is_open()) {
            throw GameException("Unable to open game_save.txt for loading!");
        }
        int population, soldiers, morale, loan, popularity, resourceCount, taxRate;
        string leaderName;
        file >> population;
        pop.setTotal(population);
        file >> soldiers >> morale;
        army.setSoldiers(soldiers);
        army.setMorale(morale);
        file >> loan;
        bank.setLoan(loan);
        file.ignore();
        getline(file, leaderName);
        file >> popularity;
        leader.setName(leaderName);
        leader.setPopularity(popularity);
        file >> resourceCount;
        ResourceManager tempRM;
        for (int i = 0; i < resourceCount; i++) {
            string resourceName;
            int amount;
            file >> resourceName >> amount;
            tempRM.gather(resourceName, amount, 0); // Use temporary RM, playerId 0 for loading
        }
        rm = tempRM; // Assign to clear existing resources
        file >> taxRate;
        economy.setTaxRate(taxRate);
        int peasantSatisfaction, merchantSatisfaction, nobleSatisfaction;
        file >> peasantSatisfaction;
        peasant.updateSatisfaction(peasantSatisfaction - peasant.getSatisfaction());
        file >> merchantSatisfaction;
        merchant.updateSatisfaction(merchantSatisfaction - merchant.getSatisfaction());
        file >> nobleSatisfaction;
        noble.updateSatisfaction(nobleSatisfaction - noble.getSatisfaction());
        file.close();
        cout << "Game loaded successfully.\n";
        return true;
    }
    catch (const GameException& e) {
        cout << "Error: " << e.message << "\n";
        return false;
    }
}