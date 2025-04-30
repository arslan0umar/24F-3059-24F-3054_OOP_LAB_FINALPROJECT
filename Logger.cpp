#include "Stronghold.h"
#include <fstream>
#include <iostream>
using namespace std;

void Logger::logScore(const string& info) {
    ofstream file("score.txt", ios::app);
    if (file.is_open()) {
        file << info << "\n";
        file.close();
        cout << "Score logged successfully to score.txt\n";
    }
    else {
        cout << "Error: Unable to open score.txt for logging\n";
    }
}

void Logger::saveGame(const Population& pop, const Army& army,
    const Bank& bank, const Leader& leader,
    const ResourceManager& rm, const Economy& economy,
    const Peasant& peasant, const Merchant& merchant, const Noble& noble) {

    ofstream file("game_save.txt");
    if (file.is_open()) {
        // Save Population
        file << "POPULATION " << pop.getTotal() << "\n";

        // Save Army
        file << "ARMY " << army.getSoldiers() << " " << army.getMorale() << "\n";

        // Save Bank
        file << "BANK " << bank.getLoan() << "\n";

        // Save Leader
        file << "LEADER " << leader.getName() << " " << leader.getPopularity() << "\n";

        // Save Economy
        file << "ECONOMY " << economy.getTaxRate() << "\n";

        // Save Social Classes
        file << "SOCIAL_CLASSES " << peasant.getSatisfaction() << " "
            << merchant.getSatisfaction() << " " << noble.getSatisfaction() << "\n";

        // Save Resources (now we save directly here rather than calling another method)
        file << "RESOURCES " << rm.getResourceCount() << "\n";
        for (int i = 0; i < rm.getResourceCount(); i++) {
            file << rm.getResourceName(i) << " " << rm.getResourceValue(i) << "\n";
        }

        file.close();
        cout << "Game state saved successfully to game_save.txt\n";
    }
    else {
        cout << "Error: Unable to open game_save.txt for saving\n";
    }
}

bool Logger::loadGame(Population& pop, Army& army, Bank& bank,
    Leader& leader, ResourceManager& rm, Economy& economy,
    Peasant& peasant, Merchant& merchant, Noble& noble) {

    ifstream file("game_save.txt");
    if (file.is_open()) {
        string marker;

        // Load Population
        if (file >> marker && marker == "POPULATION") {
            int count;
            if (file >> count) {
                pop.setTotal(count);
            }
        }

        // Load Army
        if (file >> marker && marker == "ARMY") {
            int soldiers, morale;
            if (file >> soldiers >> morale) {
                army.setSoldiers(soldiers);
                army.setMorale(morale);
            }
        }

        // Load Bank
        if (file >> marker && marker == "BANK") {
            int loan;
            if (file >> loan) {
                bank.setLoan(loan);
            }
        }

        // Load Leader
        if (file >> marker && marker == "LEADER") {
            string name;
            int popularity;

            // Handle names with spaces
            file >> name;
            string word;
            file >> word;
            // Check if this is another name part or the popularity
            while (!isdigit(word[0])) {
                name += " " + word;
                file >> word;
            }
            popularity = stoi(word);

            leader.setName(name);
            leader.setPopularity(popularity);
        }

        // Load Economy
        if (file >> marker && marker == "ECONOMY") {
            int taxRate;
            if (file >> taxRate) {
                economy.setTaxRate(taxRate);
            }
        }

        // Load Social Classes
        if (file >> marker && marker == "SOCIAL_CLASSES") {
            int peasantSat, merchantSat, nobleSat;
            if (file >> peasantSat >> merchantSat >> nobleSat) {
                // Reset first then update to match saved values
                peasant.updateSatisfaction(-100);
                merchant.updateSatisfaction(-100);
                noble.updateSatisfaction(-100);

                peasant.updateSatisfaction(peasantSat);
                merchant.updateSatisfaction(merchantSat / 2); // Adjust for the modifier in updateSatisfaction
                noble.updateSatisfaction(nobleSat * 2); // Adjust for the modifier in updateSatisfaction
            }
        }

        // Load Resources
        int resourceCount;
        if (file >> marker && marker == "RESOURCES") {
            file >> resourceCount;

            // Load each resource
            for (int i = 0; i < resourceCount; i++) {
                string name;
                int value;

                file >> name >> value;

                // Find the resource and update its value directly
                int index = rm.findResourceIndex(name);
                if (index != -1) {
                    // Reset resource first
                    rm.consume(name, rm.getResourceValue(index));
                    // Then set to saved value
                    rm.gather(name, value);
                }
            }
        }

        file.close();
        cout << "Game state loaded successfully from game_save.txt\n";
        return true;
    }
    else {
        cout << "Error: Unable to open game_save.txt for loading\n";
        return false;
    }
}